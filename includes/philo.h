/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/04/03 12:31:35 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// System .h files
// # include <string.h>
# include <pthread.h> //mutex: init destroy lock unlock
# include <stdbool.h> // boolean usage
# include <stdio.h>   //printf
# include <stdlib.h>  //malloc, free
# include <sys/_pthread/_pthread_mutex_t.h>
# include <sys/_pthread/_pthread_t.h>
# include <unistd.h>   // write, usleep
                      //threads: create join detach
# include <limits.h>   // INT_MAX
# include <sys/time.h> //gettimeofday

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RST "\033[0m"

// structs declaration
typedef pthread_mutex_t	mutex;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_fork
{
	mutex	fork;
	int		id_fork;
};

struct s_philo
{
	int			id_philo;
	int			c_meal; // counter of meals
	int			full;   // bool?
	int			l_meal; // last meal time
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	id_thread;
};

struct s_table
{
	int		n_philo;
	int		t_die;   // time to die
	int		t_eat;   // time to eat
	int		t_sleep; // time to sleep
	int		m_meals; // max meals (argv[5])
	int		s_time;  // time_start
	int		end;
	t_fork	*forks;
	t_philo	*philo;
};

// init.c
int		init_data(t_table *table, char **argv);

// clear_program.c
int		clear_program(t_table *table);

// utils
// utils.c
int		ft_atoi(const char *str);
int		str_validator(char *s);
void	error_ext(char *str);

// prints.c
int		print_struct(t_table *table);

#endif
