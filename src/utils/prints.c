/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:21:28 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/14 11:22:58 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	print_struct(t_table *table)
{
	int	i;

	i = 0;
	printf(YELLOW"Table:\n"RST);
	printf(YELLOW"-Number of philosophers: %d\n" RST, table->n_philo);
	printf(YELLOW"-Time to die: %d\n" RST, table->t_die);
	printf(YELLOW"-Time to eat: %d\n" RST, table->t_eat);
	printf(YELLOW"-Time to sleep: %d\n" RST, table->t_sleep);
	printf(YELLOW"-Number of times each philosopher"\
		"must eat: %d\n"RST, table->m_meals);
	printf("\n");

	while (i < table->n_philo)
	{
		printf(YELLOW"Philosopher %d:\n" RST, i + 1);
		printf(YELLOW"-Left fork: %p\n" RST, (void *)table->philo[i].fork_l);
		printf(YELLOW"-Right fork: %p\n" RST, (void *)table->philo[i].fork_r);
		printf(YELLOW"-Last meal time: %d\n" RST, table->philo[i].t_l_meal);
		printf(YELLOW"-Number of meals eaten: %d\n" RST, table->philo[i].c_meal);
		printf("\n");
		i++;
	}
	return (0);
}
