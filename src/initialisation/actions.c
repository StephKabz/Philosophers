/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stkabang <stkabang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:12:47 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 15:32:53 by stkabang         ###   ########.fr       */
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
	if (prog->nb_philo == 1)
	{
		pthread_mutex_lock(&prog->forks[left_fork]);
		safe_print(prog, id, "has taken a fork");
		pthread_mutex_unlock(&prog->forks[left_fork]);
		return (0);
	}
	if (id == prog->nb_philo - 1)
		return (take_two_forks(prog, id, right_fork, left_fork));
	return (take_two_forks(prog, id, left_fork, right_fork));
}

void	philosopher_eat(t_program *prog, int id)
{
	int	left_fork;
	int	right_fork;

	if (!prog)
		return ;
	left_fork = id;
	right_fork = (id + 1) % prog->nb_philo;
	if (!is_simulation_running(prog))
	{
		pthread_mutex_unlock(&prog->forks[left_fork]);
		pthread_mutex_unlock(&prog->forks[right_fork]);
		return ;
	}
	safe_print(prog, id, "is eating");
	pthread_mutex_lock(&prog->meal_lock);
	prog->meal_counts[id]++;
	prog->last_meals[id] = get_timestamp();
	pthread_mutex_unlock(&prog->meal_lock);
	precise_sleep(prog, prog->time_to_eat);
	pthread_mutex_unlock(&prog->forks[left_fork]);
	pthread_mutex_unlock(&prog->forks[right_fork]);
}

void	philosopher_sleep_action(t_program *prog, int id)
{
	if (!prog || !is_simulation_running(prog))
		return ;
	safe_print(prog, id, "is sleeping");
	precise_sleep(prog, prog->time_to_sleep);
}
