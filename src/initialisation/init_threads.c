/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:59:58 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/09 00:48:09 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_and_init_thread(t_prog *prog, t_thread_data *data)
{
	int	i;
	int	j;

	if (!prog)
		return (0);
	i = 0;
	while (i < prog->nb_philo)
	{
		data[i].prog = prog;
		data[i].philosopher_id = i;
		if (pthread_create(&prog->threads[i], NULL, philosophes_routine, &data[i]) != 0)
		{
			prog->simulation_running = 0;
			j = 0;
			while (j < i)
			{
				pthread_join(prog->threads[j], NULL);
				j++;
			}
			return (0);
		}
		i++;
	}
	free(data);
	return (1);
}

int	creates_philo_threads(t_prog *prog)
{
	t_thread_data	*data;

	prog->threads = malloc(sizeof(pthread_t) * prog->nb_philo);
	if (!prog->threads)
		return (-1);
	data = malloc(sizeof(t_thread_data) * prog->nb_philo);
	if (!data)
	{
		free(prog->threads);
		return(-1);
	}
	if (!create_and_init_thread(prog, data))
	{
		free(data);
		return (0);
	}
	return (1);
}

void	*philosophes_routine(void *arg)
{
	t_thread_data	*thread;
	t_prog			*new_prog;
	int				philo_id;
	int				left_fork;
	int				right_fork;
	int				first_fork;
	int				second_fork;
	long			current_time;
	t_philo			*my_philo;

	thread = (t_thread_data *)arg;
	new_prog = thread->prog;
	philo_id = thread->philosopher_id;
	left_fork = philo_id;
	right_fork = (philo_id + 1) % new_prog->nb_philo;
	first_fork = ft_min(left_fork, right_fork);
	second_fork = ft_max(left_fork, right_fork);
	my_philo = &new_prog->philosophers[philo_id];
	my_philo->last_meal = &new_prog->start_time;
	while (new_prog->simulation_running)
	{
		current_time = get_timestamp();
		if (current_time - my_philo->last_meal > new_prog->time_to_die)
		{
			new_prog->simulation_running = 0;
			my_philo->is_dead = 1;
			printf("Philosopher %d is dead!\n", philo_id);
			return (NULL);
		}
		printf("Philosopher %d is Thinking!\n", philo_id);
		pthread_mutex_lock(&new_prog->forks[first_fork]);
		printf("Philosopher %d has taken a fork!\n", philo_id);
		pthread_mutex_lock(&new_prog->forks[second_fork]);
		printf("Philosopher %d has taken a fork!\n", philo_id);
		printf("Philosopher %d is eating!\n", philo_id);
		my_philo->last_meal = get_timestamp();
		my_philo->meal_count++;
		sleep_time(new_prog->time_to_eat);
		pthread_mutex_unlock(&new_prog->forks[second_fork]);
		pthread_mutex_unlock(&new_prog->forks[first_fork]);
		printf("Philosopher %d is sleeping!\n", philo_id);
		sleep_time(new_prog->time_to_sleep);
	}
	return (NULL);
}
