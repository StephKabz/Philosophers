/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:11:30 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 13:40:21 by kingstephan      ###   ########.fr       */
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

#define MAX_PHILO 200

typedef struct s_program
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat; 
	int				time_to_sleep;
	int				must_eat_count;
    long long		start_time;
    int             running;
    pthread_t		threads[MAX_PHILO];
    pthread_mutex_t	forks[MAX_PHILO];
    int				meal_counts[MAX_PHILO];
    long long		last_meals[MAX_PHILO];
    pthread_t		monitor;
    pthread_mutex_t	print_lock;
    pthread_mutex_t	meal_lock;
    pthread_mutex_t	stop_lock;
}	t_program;

typedef	struct s_philo_data
{
	int			id;
	t_program	*prog;
}	t_philo_data;

// ---------- PARCE.C ---------- //
int			validate_argv_string(char *str);
int			validate_argv_value(t_program *prog);
void		init_prog_value(t_program *prog);
void		fill_program(t_program *prog, int argc, char **argv);
int			parse_arguments(t_program *prog, int argc, char **argv);

// ---------- INIT.C ---------- //
int			init_forks(t_program *prog);
int			init_control_mutex(t_program *prog);
void		init_philosopher_data(t_program *prog);
int			init_program(t_program *prog);
void		cleanup_program(t_program *prog);

// ---------- INIT_TIME.C ---------- //
long long	get_timestamp(void);
void		precise_sleep(t_program *prog, int millisecond);

// ---------- UTILS.C ---------- //
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
void		safe_print(t_program *prog, int philo_id, char *action);

// ---------- SIMULATION.C ---------- //
void		stop_simulation(t_program *prog);
int			is_simulation_running(t_program *prog);
int			create_philo_threads(t_program *prog);
void		wait_for_threads(t_program *prog);
int			start_simulation(t_program *prog);

// ---------- ROUTINE.C ---------- //
int			stop_for_meals(t_program *prog);
void		*death_monitor_routine(void *arg);
void		*philosopher_routine(void *arg);

// ---------- PHILO_ACTIONS.C ---------- //
void		philosopher_think(t_program *prog, int id);
int			philosopher_take_forks(t_program *prog, int id);
void		philosopher_eat(t_program *prog, int id);
void		philosopher_sleep_action(t_program *prog, int id);

#endif
