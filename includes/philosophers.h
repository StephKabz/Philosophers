/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:11:30 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/14 03:57:38 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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
	pthread_mutex_t	print_mutex;
	pthread_t		*threads;
}	t_prog;

typedef struct s_thread_data
{
	t_prog	*prog;
	int		philosopher_id;
}	t_thread_data;

typedef struct s_philo_contexte
{
	t_prog			*prog;
	int				philo_id;
	int				first_fork;
	int				second_fork;
	t_philo			*my_philo;;
} t_philo_contexte;

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

// ---------- INIT_THREADS.C ---------- //
int		create_and_init_thread(t_prog *prog, t_thread_data *data);
int		creates_philo_threads(t_prog *prog, t_thread_data **data_ptr);
int		check_all_have_eaten(t_prog *prog);
void	init_philo_routine(void *arg, t_philo_contexte *ctx);
void	philosophes_main_loop(t_philo_contexte *ctx);
void	*philosophes_routine(void *arg);

// ---------- PHILO_ACTION.C ---------- //
int		check_death(t_prog *prog, t_philo *my_philo, int philo_id, long current_time);
void	safe_print(t_prog *prog, char *action, int philo_id);
int		take_forks(t_prog *prog, int first_fork, int second_fork, int philo_id);
int		philosopher_eat(t_prog *prog, t_philo *my_philo, int philo_id);
void	philosopher_sleep(t_prog *prog, int philo_id);

// ---------- UTILS0.C---------- //
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

#endif