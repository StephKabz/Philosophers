/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 03:28:55 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/14 03:32:01 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_prog *prog, t_philo *my_philo, int philo_id, long current_time)
{
	if (!prog || !my_philo)
		return (0);
	if (current_time - my_philo->last_meal > prog->time_to_die)
	{
		prog->simulation_running = 0;
		my_philo->is_dead = 1;
		safe_print(prog, "is dead", philo_id);
		return (1);
	}
	return (0);
}

void	safe_print(t_prog *prog, char *action, int philo_id)
{
	if (!prog || !action)
		return ;
	pthread_mutex_lock(&prog->print_mutex);
	printf("%ld %d %s\n", get_timestamp() - prog->start_time, philo_id, action);
	pthread_mutex_unlock(&prog->print_mutex);
}

int take_forks(t_prog *prog, int first_fork, int second_fork, int philo_id)
{
	if (!prog)
		return (0);
	pthread_mutex_lock(&prog->forks[first_fork]);
	safe_print(prog, "has taken a fork", philo_id);
	if (first_fork != second_fork)
	{
		pthread_mutex_lock(&prog->forks[second_fork]);
		safe_print(prog, "has taken a fork", philo_id);
	}
	else
	{
		pthread_mutex_unlock(&prog->forks[first_fork]);
		prog->simulation_running = 0;
		//my_philo->is_dead = 1;
		safe_print(prog, "is dead", philo_id);
		return (0);
	}
	return (1);
}

int	philosopher_eat(t_prog *prog, t_philo *my_philo, int philo_id)
{
	int				left_fork;
	int				right_fork;
	int				first_fork;
	int				second_fork;

	if (!prog || !my_philo)
		return (0);
	left_fork = philo_id;
	right_fork = (philo_id + 1) % prog->nb_philo;
	first_fork = ft_min(left_fork, right_fork);
	second_fork = ft_max(left_fork, right_fork);
	safe_print(prog, "is eating", philo_id);
	my_philo->meal_count++;
	sleep_time(prog->time_to_eat);
	my_philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&prog->forks[second_fork]);
	pthread_mutex_unlock(&prog->forks[first_fork]);
	if (check_all_have_eaten(prog))
	{
		prog->simulation_running = 0;
		return (1);
	}
	return (0);
}

void	philosopher_sleep(t_prog *prog, int philo_id)
{
	if (!prog)
		return ;
	safe_print(prog, "is sleeping", philo_id);
	sleep_time(prog->time_to_sleep);
}
