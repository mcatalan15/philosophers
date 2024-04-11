/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:24:53 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/11 11:25:23 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	This function initializes the forks.
*/

int	init_forks(t_table	*table)
{
	int	i;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->fork)
		error_ext("Error: Malloc failed");
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			error_ext("Error: Mutex init failed");
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
		error_ext("Error: Malloc failed");
	pthread_mutex_lock(&table->init);
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
	if (pthread_mutex_init(&table->init, NULL) != 0)
		error_ext("Error: Mutex init failed");
	if (pthread_mutex_init(&table->print, NULL) != 0)
		error_ext("Error: Mutex print failed");
	if (pthread_mutex_init(&table->death, NULL) != 0)
		error_ext("Error: Mutex death failed");
	if (pthread_mutex_init(table->fork, NULL) != 0)
		error_ext("Error: Mutex fork failed");
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
	init_philo(table);
	return (0);
}
