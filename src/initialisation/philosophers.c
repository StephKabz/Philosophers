/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 03:28:55 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 02:04:23 by kingstephan      ###   ########.fr       */
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

void	*death_monitor_routine(void *arg)
{
	t_program	*prog;
	int			i;
	long long	current_time;

	prog = (t_program *)arg;
	while (is_simulation_running(prog))
	{
		usleep(10000);
		current_time = get_timestamp();
		pthread_mutex_lock(&prog->meal_lock);
		i = 0;
		while (i < prog->nb_philo)
		{
			if (current_time - prog->last_meals[i] > prog->time_to_die)
			{
				pthread_mutex_unlock(&prog->meal_lock);
				stop_simulation(prog);
				safe_print(prog, i, "is dead");
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&prog->meal_lock);
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
	while (is_simulation_running(prog))
	{
		if (stop_for_meals(prog))
		{
			stop_simulation(prog);
			return (NULL);
		}
		philosopher_think(prog, philo_id);
		if (philosopher_take_forks(prog, philo_id))
			philosopher_eat(prog, philo_id);
		philosopher_sleep_action(prog, philo_id);
	}
	return (NULL);
}

