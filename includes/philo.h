/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/04/15 10:37:24 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// System .h files
// # include <string.h>
# include <pthread.h> 	//mutex: init destroy lock unlock
# include <stdbool.h> 	// boolean usage
# include <stdio.h>   	//printf
# include <stdlib.h>  	//malloc, free
# include <sys/_pthread/_pthread_mutex_t.h>
# include <sys/_pthread/_pthread_t.h>
# include <unistd.h>   	// write, usleep
                      	//threads: create join detach
# include <limits.h>   	// INT_MAX
# include <sys/time.h> 	//gettimeofday
# include <string.h>		//memset

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RST "\033[0m"

// messages
# define ERROR_MALLOC "Error: Malloc failed"
# define ERROR_MTX "Error: Mutex init failed"
# define ERROR_FORKS "Error: Forks init failed"

// structs declaration
// typedef pthread_mutex_t	mutex;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_philo
{
	int				id_philo;
	int				c_meal; // counter of meals
	int				full;   // bool?
	int				t_l_meal; // last meal time
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_table			*table;
};

struct s_table
{
	int				n_philo;
	int				t_die;   	// time to die
	int				t_eat;   	// time to eat
	int				t_sleep; 	// time to sleep
	int				m_meals; 	// max meals (argv[5])
								int				t_meals;	//total meals
	int				s_time;  	// time_start
	int				end;		// philo died
	int				c_threads; 	// threads counter
	pthread_t	*philo_t; 	//	pthread_t for philo
	pthread_mutex_t	init; 		// 	pthread_pthread_mutex_t_t for init
	pthread_mutex_t	print; 		//	mutex for print
	pthread_mutex_t	*fork; 		//	mutex for forks
	pthread_mutex_t	meals;		//	mutex for meals
	pthread_mutex_t	death; 		//	mutex for death
	t_philo			*philo;
};

// init.c
int		init_data(t_table *table, char **argv);

// clear_program.c
int		clear_program(t_table *table);

// utils
// utils.c
int		ft_atoi(const char *str);
void		print_err(char *str);
int		error_mtx(t_table *table);

// prints.c
int		print_struct(t_table *table);

#endif
