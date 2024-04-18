/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:25 by mcatalan          #+#    #+#             */
/*   Updated: 2024/04/18 11:49:32 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long	time_convert(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	pause_time(long wait_time)
{
	long	start;

	start = time_convert();
	usleep(wait_time * 850); //Porq 850?
	while (time_convert() - start < wait_time)
		usleep(wait_time * 6); //Porq 6?
}
