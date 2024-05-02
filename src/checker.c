/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:08:11 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/05/02 11:19:42 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	This function is used to print the message of the philosopher's death.
*/

void	death_print(t_table *table, int i)
{
	table->is_dead = 1;
	pthread_mutex_lock(&(table->print));
	printf("%lld %d %s\n", ms_time() - table->t_creation,
		table->philo[i].id + 1, "died");
}

/*
	This function checks if the philosopher has died or if the number of meals
	indicated in argv[5] has been reached. If the philosopher has died, the
	function death_print is called.
*/

void	*checker(t_table *table)
{
	int	i;

	while (table->is_dead == 0)
	{
		i = -1;
		while (++i < table->n_philo)
		{
			if (table->t_meals == (table->n_philo * table->m_meals))
				return (NULL);
			if (((ms_time() - table->philo[i].l_meal) > table->t_die)
				&& (table->philo[i].c_meal != table->m_meals))
			{
				death_print(table, i);
				break ;
			}
		}
	}
	return (NULL);
}

/*
	This function is used to initialice the function that checks if a philosopher
	has died or if all the philosophers have eaten the number of meals indicated
	in argv[5].
*/

void	*check_final(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (table->active_threads != table->n_philo)
		wait_t(1);
	table->t_creation = ms_time();
	wait_t(table->t_eat / 2);
	checker(table);
	return (NULL);
}
