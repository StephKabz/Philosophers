/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:12:47 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 01:49:13 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_think(t_program *prog, int id)
{
	if (!prog || !is_simulation_running(prog))
		return ;
	safe_print(prog, id, "is thinking");
}

int	philosopher_take_forks(t_program *prog, int id)
{
	int	left_fork;
	int	right_fork;

	if (!prog || !is_simulation_running(prog))
		return (0);
	left_fork = id;
	right_fork = (id + 1) % prog->nb_philo;
	if (id == prog->nb_philo - 1)
	{
		pthread_mutex_lock(&prog->forks[right_fork]);
		safe_print(prog, id, "has taken a fork");
		if (prog->nb_philo == 1)
		{
			pthread_mutex_unlock(&prog->forks[right_fork]);
			return (0);
		}
		pthread_mutex_lock(&prog->forks[left_fork]);
		safe_print(prog, id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&prog->forks[left_fork]);
		safe_print(prog, id, "has taken a fork");
		pthread_mutex_lock(&prog->forks[right_fork]);
		safe_print(prog, id, "has taken a fork");
	}
	return (1);
}

void	philosopher_eat(t_program *prog, int id)
{
	int	left_fork;
	int	right_fork;

	if (!prog || !is_simulation_running(prog))
		return ;
	left_fork = id;
	right_fork = (id + 1) % prog->nb_philo;
	safe_print(prog, id, "is eating");
	pthread_mutex_lock(&prog->meal_lock);
	prog->meal_counts[id]++;
	prog->last_meals[id] = get_timestamp();
	pthread_mutex_unlock(&prog->meal_lock);
	precise_sleep(prog, prog->time_to_eat);
	if (id == prog->nb_philo - 1)
	{
		pthread_mutex_unlock(&prog->forks[left_fork]);
		pthread_mutex_unlock(&prog->forks[right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&prog->forks[left_fork]);
		pthread_mutex_unlock(&prog->forks[right_fork]);
	}
}

void	philosopher_sleep_action(t_program *prog, int id)
{
	if (!prog || !is_simulation_running(prog))
		return ;
	safe_print(prog, id, "is sleeping");
	precise_sleep(prog, prog->time_to_sleep);
}
