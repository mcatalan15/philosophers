/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:24:53 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/27 13:17:46 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	Initializes the values of the philo structure, first allocating
	memory for all the information. Then it sets the order for the forks
	from right to left, and the last philosopher has the first fork.
*/

int	init_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!(table->philo))
		return (print_err(ERROR_MALLOC));
	i = 0;
	while (i < table->n_philo)
	{
		table->philo[i].id = i;
		table->philo[i].c_meal = 0;
		table->philo[i].table = table;
		table->philo[i].r_fork = &table->forks[i];
		table->philo[i].l_fork = &table->forks[i + 1];
		i++;
	}
	table->philo[i - 1].l_fork = &table->forks[0];
	return (0);
}

/*
	This function initializes the mutexes used for control the forks.
	Each fork is a mutex, so the philosophers can take them and release
	them without problems.
*/

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (print_err(ERROR_MALLOC));
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (print_err(ERROR_MTX));
		i++;
	}
	return (0);
}

/*
	This function initialize the mutexes used for control the acctions.
	This way we can avoid problems with the threads.
	- init: used to control the creation of the threads.
	- print: used to control the print of the status messages.
	- meals_mtx: used to control the number of meals eaten by the
		philosophers.
*/

int	init_mtx(t_table *table)
{
	if (pthread_mutex_init(&table->init, NULL))
		return (print_err(ERROR_MTX));
	if (pthread_mutex_init(&table->print, NULL))
		return (print_err(ERROR_MTX));
	if (pthread_mutex_init(&table->meals_mtx, NULL))
		return (print_err(ERROR_MTX));
	return (0);
}

/*
	This function initializes the table structure with the information
	provided by the input arguments. Also, it sets the default values
	for the rest of the table structure values.
*/

int	init_table(char **argv, t_table *table)
{
	table->n_philo = ft_atol(argv[1]);
	table->t_die = ft_atol(argv[2]);
	table->t_eat = ft_atol(argv[3]);
	table->t_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->m_meals = ft_atol(argv[5]);
	else
		table->m_meals = INT_MAX;
	table->forks = NULL;
	table->philo = NULL;
	table->philos_th = NULL;
	table->t_meals = 0;
	table->is_dead = 0;
	table->active_threads = 0;
	table->t_creation = 0;
	return (0);
}

/*
	Funtion to initialize all the information of the table, philo
	structures and mutexes.
	Divided in 4 functions to make it more readable and easier to
	handle errors.
*/

int	init_info(char **argv, t_table *table)
{
	init_table(argv, table);
	if (init_mtx(table))
		return (EXIT_FAILURE);
	if (init_forks(table))
		return (EXIT_FAILURE);
	if (init_philos(table))
		return (EXIT_FAILURE);
	return (0);
}
