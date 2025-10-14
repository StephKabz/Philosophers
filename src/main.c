/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:55:09 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/14 04:45:40 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clean_prog(t_prog *prog)
{
	int	j;

	if (!prog)
		return ;
	j = 0;
	if (prog->forks)
	{
		while (j < prog->nb_philo)
		{
			pthread_mutex_destroy(&prog->forks[j]);
			j++;
		}
		pthread_mutex_destroy(&prog->print_mutex);
		free(prog->forks);
	}
	if (prog->philosophers)
		free(prog->philosophers);
	free(prog);
}

static void	wait_for_threads(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		pthread_join(prog->threads[i], NULL);
		i++;
	}
	free(prog->threads);
	prog->threads = NULL;
}

static t_prog	*parse_and_init(int argc, char **argv)
{
	t_args	*args;
	t_prog	*prog;

	args = create_args(argc, argv);
	if (!args || !validate_args(args))
	{
		if (args)
			free(args);
		printf("Error : Invalid Arguments!\n");
		return (NULL);
	}
	prog = init_program(args);
	if (!prog)
	{
		free(args);
		printf("Error : Initilization Failed\n");
		return (NULL);
	}
	free(args);
	return (prog);
}

static int	start_simulation(t_prog *prog, t_thread_data **thread_data)
{
	if (!prog)
		return (0);
	prog->start_time = get_timestamp();
	prog->simulation_running = 1;
	if (creates_philo_threads(prog, thread_data) != 1)
	{
		clean_prog(prog);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_args			*args;
	t_prog			*prog;
	t_thread_data	*thread_data;

	args = create_args(argc, argv);
	if (!args || !validate_args(args))
	{
		if (args)
			free(args);
		printf("Error : Invalid Arguments!\n");
		return (1);
	}
	prog = parse_and_init(argc, argv);
	if (!start_simulation(prog, &thread_data))
		return (1);
	wait_for_threads(prog);
	free(thread_data);
	clean_prog(prog);
	return (0);
}
