/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:55:09 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/11 16:49:26 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_prog(t_prog *prog)
{
	int	i;
	int	j;

	if (!prog)
		return ;
	i = 0;
	j = 0;
	if (prog->threads)
	{
		while (i < prog->nb_philo)
		{
			pthread_join(prog->threads[i], NULL);
			i++;
		}
		free(prog->threads);
	}
	if (prog->forks)
	{
		while (j++ < prog->nb_philo)
		{
			pthread_mutex_destroy(&prog->forks[j]);
			j++;
		}
		free(prog->forks);
	}
	if (prog->philosophers)
		free(prog->philosophers);
	free(prog);
}

void	wait_for_threads(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philo)
	{
		pthread_join(prog->threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_prog	*prog;
	

	args = create_args(argc, argv);
	if (!args || !validate_args(args))
	{
		if (args)
			free(args);
		printf("Error : Invalid Arguments!\n");
		return (1);
	}
	prog = init_program(args);
	if (!prog)
	{
		free(args);
		printf("Error : Initilization Failed\n");
		return (1);
	}
	free(args);
	prog->start_time = get_timestamp();
	prog->simulation_running = 1;
	if (creates_philo_threads(prog) != 1)
	{
		clean_prog(prog);
		return (1);
	}
	wait_for_threads(prog);
	clean_prog(prog);
	return (0);
}
