/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:21:28 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/28 12:04:02 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
	This function is used to print all the values of the table and the
	philosophers. It is used for debugging purposes.
*/

int	print_struct(t_table *table)
{
	int	i;

	i = 0;
	printf(YLW"Table:\n"RST);
	printf(YLW"-Number of philosophers: %d\n" RST, table->n_philo);
	printf(YLW"-Time to die: %d\n" RST, table->t_die);
	printf(YLW"-Time to eat: %d\n" RST, table->t_eat);
	printf(YLW"-Time to sleep: %d\n" RST, table->t_sleep);
	printf(YLW"-Number of times each philosopher"\
		"must eat: %d\n"RST, table->m_meals);
	printf("\n");
	while (i < table->n_philo)
	{
		printf(YLW"Philosopher %d:\n" RST, i + 1);
		printf(YLW"-ID: %d\n" RST, table->philo[i].id);
		printf(YLW"-l_fork fork: %p\n" RST, (void *)table->philo[i].l_fork);
		printf(YLW"-r_fork fork: %p\n" RST, (void *)table->philo[i].r_fork);
		printf(YLW"-Last meal time: %lld\n" RST, table->philo[i].l_meal);
		printf(YLW"-Number of meals eaten: %d\n" RST, table->philo[i].c_meal);
		printf("\n");
		i++;
	}
	return (0);
}

/*
	This function is used to print the total number of meals served and the
	number of times each philosopher has eaten. Used for debugging purposes.
*/

void	print_totals(t_table *table)
{
	wait_t(table->t_eat + table->t_sleep);
	if ((table->m_meals != INT_MAX) && (table->is_dead == 0))
	{
		pthread_mutex_lock(&table->print);
		printf("Each philosopher ate: %d times\n", table->m_meals);
		printf("Total served meals: %d\n", table->t_meals);
		pthread_mutex_unlock(&table->print);
	}
}

/*
	This function is used to print the error message, clear the program and return
	EXIT_FAILURE.
*/

int	print_err2(t_table *table)
{
	table->t_creation = 1;
	table->is_dead = 1;
	wait_t(1);
	print_err(ERROR_THREADS_I);
	clear_program(table);
	return (1);
}

/*
	This function is used to print the error message and return EXIT_FAILURE.
*/

int	print_err(char *str)
{
	printf(RED "Error: %s\n" RST, str);
	return (EXIT_FAILURE);
}

/*
	This function is used to print the status of the philosopher. When its called
	with the message of the status, the function locks the print mutex, prints the
	message and unlocks the mutex.
*/

void	print_status(t_philo *philo, int id, char *msg)
{
	if (philo->table->is_dead == 0)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld ", (ms_time() - philo->table->t_creation));
		printf("%d ", id + 1);
		printf("%s\n", msg);
		pthread_mutex_unlock(&philo->table->print);
	}
}
