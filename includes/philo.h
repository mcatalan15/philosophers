/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:03:49 by mcatalan          #+#    #+#             */
/*   Updated: 2024/03/25 10:35:52 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// System .h files
// # include <string.h>
# include <stdio.h>		//printf
# include <stdlib.h>	//malloc, free
# include <unistd.h>	// write, usleep
# include <stdbool.h>	// boolean usage
# include <pthread.h>	//mutex: init destroy lock unlock
						//threads: create join detach
# include <sys/time.h>	//gettimeofday
# include <limits.h>	// INT_MAX

typedef struct s_philo
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct s_table	*table;
}	t_philo;

// utils
// utils.c
int	ft_atoi(const char *str);

#endif
