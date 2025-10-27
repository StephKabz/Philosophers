/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:49:42 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 00:25:58 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_argv_string(char *str)
{
	int	i;

	if (!str || ft_strlen(str) == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_argv_value(t_program *prog)
{
	if (prog->nb_philo <= 0 || prog->nb_philo > MAX_PHILO)
		return (0);
	if (prog->time_to_die <= 0)
		return (0);
	if (prog->time_to_eat <= 0)
		return (0);
	if (prog->time_to_sleep <= 0)
		return (0);
	if (prog->must_eat_count < -1 || prog->must_eat_count == 0)
		return (0);
	return (1);
}

void	init_prog_value(t_program *prog)
{
	int	i;

	prog->start_time = 0;
	prog->running = 1;
	i = 0;
	while (i < MAX_PHILO)
	{
		prog->meal_counts[i] = 0;
		prog->last_meals[i] = 0;
		i++;
	}
}

void	fill_program(t_program *prog, int argc, char **argv)
{
	prog->nb_philo = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		prog->must_eat_count = ft_atoi(argv[5]);
	else
		prog->must_eat_count = -1;
}

int	parse_arguments(t_program *prog, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error : Wrong number of arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!validate_argv_string(argv[i]))
		{
			printf("Error : Invalid arguments\n");
			return (1);
		}
		i++;
	}
	fill_program(prog, argc, argv);
	init_prog_value(prog);
	if (!validate_argv_value(prog))
	{
		printf("Error : Invalid parameter value\n");
		return (1);
	}
	return (0);
}
