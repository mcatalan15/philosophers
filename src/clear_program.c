/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:31:30 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/27 12:16:16 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	This function is used to destroy all the mutexes (forks and controllers).
	Then it frees the memory allocated for the forks and the philosophers.
*/

int	clear_program(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philo)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->init);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->meals_mtx);
	if (table->philo)
		free(table->philo);
	if (table->philos_th)
		free(table->philos_th);
	if (table->forks)
		free(table->forks);
	return (0);
}
