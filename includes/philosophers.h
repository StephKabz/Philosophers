/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:11:30 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/10 00:22:35 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int		position;
	long	last_meal;
	int		is_dead;
	int		meal_count;
}	t_philo;

typedef struct s_args
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}	t_args;

typedef struct s_prog
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				simulation_running;
	t_philo			*philosophers;
	pthread_mutex_t *forks;
	pthread_t		*threads;
}	t_prog;

typedef struct s_thread_data
{
	t_prog	*prog;
	int		philosopher_id;
}	t_thread_data;

// ---------- PARSE.C ---------- //
int		check_args_char(char *str);
t_args	*create_args(int argc, char **argv);
int		validate_args(t_args *args);

// ---------- INIT_PROG.C ---------- //
void	copie_args_and_init(t_prog *prog ,t_args *args);
void	init_philosophers(t_prog *prog);
int		init_mutex(t_prog *prog);
void	free_mutex(t_prog *prog, int mutex_count);
t_prog	*init_program(t_args *args);

// ---------- INIT_TIME.C ---------- //
long	get_timestamp(void);
long	time_diff(long start, long current);
void	sleep_time(int milliseconde);

// ---------- INIT_TIME.C ---------- //
int		create_and_init_thread(t_prog *prog, t_thread_data *data);
int		creates_philo_threads(t_prog *prog);
void	*philosophes_routine(void *arg);

// ---------- UTILS0.C---------- //
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

#endif