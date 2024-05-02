/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:08:04 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/05/02 10:43:49 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	This function is key to manage the eating process: it locks the left fork,
	prints a message, locks the right fork, prints a message, then manages the
	eating time, records the last meal time, counts the meals and unlocks the
	mutexes.
*/

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, philo->id, "has taken a fork");
	print_status(philo, philo->id, "is eating");
	philo->l_meal = ms_time();
	if (philo->table->is_dead == 0)
		wait_t(philo->table->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->table->m_meals != INT_MAX)
	{
		philo->c_meal++;
		pthread_mutex_lock(&philo->table->meals_mtx);
		philo->table->t_meals++;
		pthread_mutex_unlock(&philo->table->meals_mtx);
	}
}

/*
	This function is the main routine used to make each philosopher eat, sleep
	and think. It also controls the number of meals eaten by each philosopher
	and the time of the last meal.
*/

void	*actions(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->init);
	philo->table->active_threads++;
	pthread_mutex_unlock(&philo->table->init);
	while (philo->table->t_creation == 0)
		wait_t(1);
	philo->l_meal = philo->table->t_creation;
	if (philo->table->n_philo == 1)
	{
		print_status(philo, philo->id, "has taken a fork");
		return (NULL);
	}
	if (philo->id % 2 == 1)
		wait_t(philo->table->t_eat / 2);
	while (philo->table->is_dead == 0 && philo->c_meal < philo->table->m_meals)
	{
		eat(philo);
		print_status(philo, philo->id, "is sleeping");
		if (philo->table->is_dead == 0)
			wait_t(philo->table->t_sleep);
		print_status(philo, philo->id, "is thinking");
	}
	return (NULL);
}

/*
	This function is used to create the threads for each
	philosopher.Each thread is created and detached, so we
	can control the end of the program with the check_death
	thread and check_final function.
*/

int	exec_program(t_table *table)
{
	int	i;

	i = -1;
	table->philos_th = malloc(sizeof(pthread_t) * table->n_philo);
	if (!table->philos_th)
		return (print_err(ERROR_MALLOC));
	while (++i < table->n_philo)
	{
		if (pthread_create(&table->philos_th[i],
				NULL, &actions, (void *)&table->philo[i]) != 0)
			return (print_err(ERROR_THREADS_I));
		if (pthread_detach(table->philos_th[i]) != 0)
			return (print_err(ERROR_THREADS_D));
	}
	if (pthread_create(&table->check_death, NULL,
			&check_final, (void *)table) != 0)
		print_err2(table);
	pthread_join(table->check_death, NULL);
	return (0);
}
