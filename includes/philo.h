/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/04/28 13:36:49 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YLW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RST "\033[0m"

// errors
# define ERROR_NARGS "Number of arguments wrong\n\tMust be 4 or 5."
# define ERROR_NPHILO "Number of philosophers:\n\tBetween 1 and 200 included."
# define ERROR_NTIME "Time:\n\tBetween 60ms and 2147483647ms. Both included."
# define ERROR_NMEALS "Numer of meals:\n\tBetween 1 and 2147483647 included."
# define ERROR_MALLOC "\n\tMalloc failed"
# define ERROR_MTX "\n\tMutex init failed"
# define ERROR_FORKS "\n\tForks init failed"
# define ERROR_THREADS_I "\n\tThreads init failed"
# define ERROR_THREADS_D "\n\tThreads death check failed"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int						id;
	int						c_meal;
	long long				l_meal;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	t_table					*table;
}	t_philo;

typedef struct s_table
{
	int						n_philo;
	int						t_die;
	int						t_eat;
	int						t_sleep;
	int						m_meals;
	int						t_meals;
	long long				t_creation;
	int						is_dead;
	int						active_threads;
	pthread_t				*philos_th;
	pthread_t				check_death;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print;
	pthread_mutex_t			init;
	pthread_mutex_t			meals_mtx;
	t_philo					*philo;
}	t_table;

// init.c
int				init_info(char **argv, t_table *table);

//program.c
int				exec_program(t_table *table);

// checker.c
void			*check_final(void *data);
void			death_print(t_table *table, int i);

// clear_program.c
int				clear_program(t_table *table);

// utils
// parsing.c
int				parsing(char **argv);

// prints.c
int				print_err(char *str);
int				print_err2(t_table *table);
int				print_struct(t_table *table);
void			print_totals(t_table *table);
void			print_status(t_philo *philo, int id, char *msg);

// time.c
long			ms_time(void);
void			wait_t(long wait_time);

// ft_atol.c
long long int	ft_atol(const char *str);

#endif
