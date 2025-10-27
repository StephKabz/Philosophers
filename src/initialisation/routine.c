/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stkabang <stkabang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 03:28:55 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 15:36:32 by stkabang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	stop_for_meals(t_program *prog)
{
	int	i;
	int	total_meals;

	if (prog->must_eat_count <= 0)
		return (0);
	pthread_mutex_lock(&prog->meal_lock);
	total_meals = 0;
	i = 0;
	while (i < prog->nb_philo)
	{
		total_meals += prog->meal_counts[i];
		i++;
	}
	pthread_mutex_unlock(&prog->meal_lock);
	return (total_meals >= prog->nb_philo * prog->must_eat_count);
}

int	check_philosopher_death(t_program *prog, int i, long long c_time)
{
	if (c_time - prog->last_meals[i] > prog->time_to_die)
	{
		pthread_mutex_unlock(&prog->meal_lock);
		stop_simulation(prog);
		safe_print(prog, i, "died");
		return (1);
	}
	return (0);
}

int	check_all_deaths(t_program *prog)
{
	long long	current_time;
	int			i;

	current_time = get_timestamp();
	pthread_mutex_lock(&prog->meal_lock);
	i = 0;
	while (i < prog->nb_philo)
	{
		if (check_philosopher_death(prog, i, current_time))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&prog->meal_lock);
	return (0);
}

void	*death_monitor_routine(void *arg)
{
	t_program	*prog;

	prog = (t_program *)arg;
	while (is_simulation_running(prog))
	{
		usleep(1000);
		if (check_all_deaths(prog))
			return (NULL);
		if (stop_for_meals(prog))
		{
			stop_simulation(prog);
			return (NULL);
		}
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo_data	*data;
	int				philo_id;
	t_program		*prog;

	data = (t_philo_data *)arg;
	philo_id = data->id;
	prog = data->prog;
	if (philo_id % 2 == 1)
		usleep(1000);
	while (is_simulation_running(prog))
	{
		philosopher_think(prog, philo_id);
		if (!philosopher_take_forks(prog, philo_id))
			break ;
		philosopher_eat(prog, philo_id);
		philosopher_sleep_action(prog, philo_id);
	}
	return (NULL);
}
