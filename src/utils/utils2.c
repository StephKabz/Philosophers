/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stkabang <stkabang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:31:18 by stkabang          #+#    #+#             */
/*   Updated: 2025/10/27 15:31:53 by stkabang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_one_fork(t_program *prog, int id, int fork_id)
{
	pthread_mutex_lock(&prog->forks[fork_id]);
	if (!is_simulation_running(prog))
	{
		pthread_mutex_unlock(&prog->forks[fork_id]);
		return (0);
	}
	safe_print(prog, id, "has taken a fork");
	return (1);
}

int	take_two_forks(t_program *prog, int id, int first, int second)
{
	pthread_mutex_lock(&prog->forks[first]);
	if (!is_simulation_running(prog))
	{
		pthread_mutex_unlock(&prog->forks[first]);
		return (0);
	}
	safe_print(prog, id, "has taken a fork");
	pthread_mutex_lock(&prog->forks[second]);
	if (!is_simulation_running(prog))
	{
		pthread_mutex_unlock(&prog->forks[second]);
		pthread_mutex_unlock(&prog->forks[first]);
		return (0);
	}
	safe_print(prog, id, "has taken a fork");
	return (1);
}
