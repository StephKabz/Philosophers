/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:49:42 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/14 05:29:53 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args_char(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (ft_strlen(str) == 0)
		return (-1);
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (-1);
		i++;
	}
	return (1);
}

t_args	*create_args(int argc, char **argv)
{
	t_args	*args;
	int		i;

	i = 1;
	if (!(argc >= 5 && argc <= 6))
		return (NULL);
	while (i < argc)
	{
		if (check_args_char(argv[i]) != 1)
			return (NULL);
		i++;
	}
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->nb_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		args->must_eat_count = -1;
	else
		args->must_eat_count = ft_atoi(argv[5]);
	return (args);
}

int	validate_args(t_args *args)
{
	if (!args)
		return (-1);
	if (args->nb_philo <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		return (-1);
	if (args->must_eat_count <= 0 && args->must_eat_count != -1)
		return (-1);
	return (1);
}
