/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:25 by mcatalan          #+#    #+#             */
/*   Updated: 2024/04/28 12:04:16 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
	This function calculates the current time in milliseconds.
*/

long	ms_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/*
	This function is used to pause the program for a certain amount of time.
	Uses usleep and ms_time to pause the program for a certain amount of time
*/

void	wait_t(long wait_time)
{
	long	start;

	start = ms_time();
	usleep(wait_time * 850);
	while (ms_time() - start < wait_time)
		usleep(wait_time * 6);
}
