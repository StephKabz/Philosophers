/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:55:09 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/09 23:30:23 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	prog->start_time = get_timestamp();
	prog->simulation_running = 1;
	if (creates_philo_threads(prog) != 1)
	{
		free(args);
		free(prog);
		return (1);
	}
	free(args);
	free(prog);
	return (0);
}
