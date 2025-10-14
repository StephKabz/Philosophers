/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:59:58 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/14 04:02:26 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	return (1);
}

int	creates_philo_threads(t_prog *prog, t_thread_data **data_ptr)
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
	*data_ptr = data;
	return (1);
}

int	check_all_have_eaten(t_prog *prog)
{
	int	i;

	if (!prog)
		return (0);
	if (prog->must_eat_count <= 0)
		return (0);
	i = 0;
	while (i < prog->nb_philo)
	{
		if (prog->philosophers[i].meal_count < prog->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void	init_philo_routine(void *arg, t_philo_contexte *ctx)
{
	t_thread_data	*thread;
	int				left_fork;
	int				right_fork;

	if (!ctx)
		return ;
	thread = (t_thread_data *)arg;
	ctx->prog = thread->prog;
	ctx->philo_id = thread->philosopher_id;
	left_fork = ctx->philo_id;
	right_fork = (ctx->philo_id + 1) % ctx->prog->nb_philo;
	ctx->first_fork = ft_min(left_fork, right_fork);
	ctx->second_fork = ft_max(left_fork, right_fork);
	ctx->my_philo = &ctx->prog->philosophers[ctx->philo_id];
	ctx->my_philo->last_meal = ctx->prog->start_time;
}

void	philosophes_main_loop(t_philo_contexte *ctx)
{
	long	current_time;
	int		fork_result;

	while (ctx->prog->simulation_running)
	{
		current_time = get_timestamp();
		if (check_death(ctx->prog, ctx->my_philo, ctx->philo_id, current_time))
			return ;
		safe_print(ctx->prog, "is thinking", ctx->philo_id);
		fork_result = take_forks(ctx->prog, ctx->first_fork, ctx->second_fork, ctx->philo_id);
		if (fork_result <= 0)
		{
			if (fork_result == -1)
				ctx->my_philo->is_dead = 1;
			return ;
		}
		
		if (philosopher_eat(ctx->prog, ctx->my_philo, ctx->philo_id))
			return ;
		philosopher_sleep(ctx->prog, ctx->philo_id);
	}
	return ;
}

void	*philosophes_routine(void *arg)
{
	t_philo_contexte ctx;

	init_philo_routine(arg, &ctx);
	philosophes_main_loop(&ctx);
	return (NULL);
}
