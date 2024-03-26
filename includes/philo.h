/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/26 11:11:39 by mcatalan@st      ###   ########.fr       */
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
# define RESET "\033[0m"

// structs declaration
typedef pthread_mutex_t	t_mtx;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		id_fork;
}			t_fork;

typedef struct s_philo
{
	int			id_philo;
	int			c_meal; // counter of meals
	int			full;   // bool?
	int			l_meal; // last meal time
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	id_thread;
}				t_philo;

typedef struct s_table
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
}			t_table;

// utils
// utils.c
int	ft_atoi(const char *str);

#endif
