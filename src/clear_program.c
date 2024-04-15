/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:31:30 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/14 20:42:20 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	destroy_data function is used to free the memory allocated in the program.
*/

int	clear_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->init);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->meals);
	if (table->philo)
		free(table->philo);
	if (table->fork)
		free(table->fork);
	return (0);
}
