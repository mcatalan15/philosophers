/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:24:53 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/15 11:40:45 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	This function initializes the forks.
*/

int	init_forks(t_table	*table)
{
	int	i;

	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->fork)
	{
		print_err(ERROR_MALLOC);
		return (EXIT_FAILURE);
	}
	i= 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			print_err(ERROR_FORKS);
		i++;
	}
	return (0);
}

/*
	This function initializes the philo struct data.
*/

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
	{
		print_err(ERROR_MALLOC);
		return (EXIT_FAILURE);
	}
	while (i < table->n_philo)
	{
		table->philo[i].id_philo = i + 1;
		table->philo[i].c_meal = 0;
		table->philo[i].full = 0;
		table->philo[i].t_l_meal = 0;
		table->philo[i].fork_l = &table->fork[i];
		table->philo[i].fork_r = &table->fork[(i + 1) % table->n_philo];
		i++;
	}
	table->philo[i -1].fork_r = &table->fork[0];
	return (0);
}

/*
	This function initializes the mutex variables.
*/

int	init_mtx(t_table *table)
{
	if (pthread_mutex_init(&table->init, NULL))
	{
		print_err(ERROR_MTX);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&table->print, NULL))
	{
		print_err(ERROR_MTX);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&table->meals, NULL))
	{
		print_err(ERROR_MTX);
		return (EXIT_FAILURE);
	}
	return (0);
}

/*
	This function sets the data of the table.
*/

int	init_table(t_table *table, char **argv)
{
	table->n_philo = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->m_meals = ft_atoi(argv[5]);
	else
		table->m_meals = -1;
	table->end = 0;
	table->c_threads = 0;
	table->fork = NULL;
	table->philo_t = NULL;
	table->philo = NULL;
	table->s_time = 0;
	return (0);
}

/*
	This function initializes the data needed for the program.
	With this function, we can set up the mutexes, the threads, the forks, etc.
	Also we avoid segmentation faults that can be caused because some variables
	are not initialized.
	./philo philos time_to_die time_to_eat time_to_sleep [optional: max_meals]
*/

int	init_data(t_table *table, char **argv)
{
	init_table(table, argv);
	if (init_forks(table))
		return (EXIT_FAILURE);
	if (init_philo(table))
		return (EXIT_FAILURE);
	if (init_mtx(table))
		return (EXIT_FAILURE);
	return (0);
}
