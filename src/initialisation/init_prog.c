/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:49:47 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/13 22:11:29 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	copie_args_and_init(t_prog *prog ,t_args *args)
{
	if (!args || !prog)
		return ;
	prog->nb_philo = args->nb_philo;
	prog->time_to_die = args->time_to_die;
	prog->time_to_eat = args->time_to_eat;
	prog->time_to_sleep = args->time_to_sleep;
	prog->must_eat_count = args->must_eat_count;
	prog->start_time = 0;
	prog->simulation_running = 1;
}

void	init_philosophers(t_prog *prog)
{
	int	i;

	if (!prog)
		return ;
	i = 0;
	while (i < prog->nb_philo)
	{
		prog->philosophers[i].position = i;
		prog->philosophers[i].is_dead = 0;
		prog->philosophers[i].meal_count = 0;
		prog->philosophers[i].last_meal = 0;
		i++;
	}
}

int	init_mutex(t_prog *prog)
{
	int	i;

	if (!prog)
		return (-1);
	i = 0;
	while (i < prog->nb_philo)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
		{
			free_mutex(prog, i);
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&prog->print_mutex, NULL) != 0)
		{
			free_mutex(prog, prog->nb_philo);
			return (-1);
		}
	return (0);
}

void	free_mutex(t_prog *prog, int mutex_count)
{
	int	i;

	i = 0;
	while (i < mutex_count)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prog->print_mutex);
	free(prog->forks);
	free(prog->philosophers);
	free(prog);
}

t_prog	*init_program(t_args *args)
{
	t_prog	*prog;

	if (!args)
		return (NULL);
	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	copie_args_and_init(prog, args);
	prog->philosophers = malloc(sizeof(t_philo) * prog->nb_philo);
	if (!prog->philosophers)
	{
		free(prog);
		return (NULL);
	}
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->nb_philo);
	if (!prog->forks)
	{
		free(prog->philosophers);
		free(prog);
		return (NULL);
	}
	if (init_mutex(prog) != 0)
		return (NULL);
	init_philosophers(prog);
	return (prog);
}
