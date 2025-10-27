/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:59:58 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 14:04:40 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	stop_simulation(t_program *prog)
{
	if (!prog)
		return ;
	pthread_mutex_lock(&prog->stop_lock);
	prog->running = 0;
	pthread_mutex_unlock(&prog->stop_lock);
}

int	is_simulation_running(t_program *prog)
{
	int	running;

	if (!prog)
		return (0);
	pthread_mutex_lock(&prog->stop_lock);
	running = prog->running;
	pthread_mutex_unlock(&prog->stop_lock);
	return (running);
}

int	create_philo_threads(t_program *prog)
{
	int				i;
	t_philo_data	*philo_data;

	philo_data = malloc(sizeof(t_philo_data) * prog->nb_philo);
	if (!philo_data)
		return (1);
	i = 0;
	while (i < prog->nb_philo)
	{
		philo_data[i].id = i;
		philo_data[i].prog = prog;
		if (pthread_create(&prog->threads[i], NULL, philosopher_routine, &philo_data[i]) != 0)
		{
			stop_simulation(prog);
			while (--i >= 0)
				pthread_join(prog->threads[i], NULL);
			free(philo_data);
			return (1);
		}
		i++;
	}
	usleep(100);
	free(philo_data);
	return (0);
}

void	wait_for_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		pthread_join(prog->threads[i], NULL);
		i++;
	}
	pthread_join(prog->monitor, NULL);
}

int	start_simulation(t_program *prog)
{
	int	i;

	if (!prog)
		return (1);
	prog->start_time = get_timestamp();
	i = 0;
	while (i < prog->nb_philo)
	{
		prog->last_meals[i] = prog->start_time;
		i++;
	}
	if (pthread_create(&prog->monitor, NULL, death_monitor_routine, prog) != 0)
	{
		printf("Error : failed to create monitor thread\n");
		return (1);
	}
	if (create_philo_threads(prog) != 0)
	{
		printf("Error : failed to create philosophers threads\n");
		stop_simulation(prog);
		pthread_join(prog->monitor, NULL);
		return (1);
	}
	wait_for_threads(prog);
	return (0);
}
