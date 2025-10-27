/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:49:47 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 00:28:12 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&prog->forks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_control_mutex(t_program *prog)
{
	if (pthread_mutex_init(&prog->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&prog->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&prog->print_lock);
		return (1);
	}
	if (pthread_mutex_init(&prog->stop_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&prog->print_lock);
		pthread_mutex_destroy(&prog->meal_lock);
		return (1);
	}
	return (0);
}

void	init_philosopher_data(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		prog->meal_counts[i] = 0;
		prog->last_meals[i] = 0;
		i++;
	}
}

int	init_program(t_program *prog)
{
	if (!prog)
		return (1);
	if (init_control_mutex(prog) != 0)
	{
		printf("Error : Failed to initialize control mutex\n");
		return (1);
	}
	if (init_forks(prog))
	{
		pthread_mutex_destroy(&prog->print_lock);
		pthread_mutex_destroy(&prog->meal_lock);
		pthread_mutex_destroy(&prog->stop_lock);
		printf("Error : failed to initialize forks\n");
		return (1);
	}
	init_philosopher_data(prog);
	return (0);
}

void	cleanup_program(t_program *prog)
{
	int	i;

	if (!prog)
		return ;
	i = 0;
	while (i < prog->nb_philo)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prog->print_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->stop_lock);
}
