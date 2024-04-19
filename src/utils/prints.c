/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:21:28 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/19 10:42:20 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	print_struct(t_table *table)
{
	int	i;

	i = 0;
	printf(YLW"Table:\n"RST);
	printf(YLW"-Number of philosophers: %d\n" RST, table->n_philo);
	printf(YLW"-Time to die: %ld\n" RST, table->t_die);
	printf(YLW"-Time to eat: %ld\n" RST, table->t_eat);
	printf(YLW"-Time to sleep: %ld\n" RST, table->t_sleep);
	printf(YLW"-Number of times each philosopher"\
		"must eat: %d\n"RST, table->m_meals);
	printf("\n");
	while (i < table->n_philo)
	{
		printf(YLW"Philosopher %d:\n" RST, i + 1);
		printf(YLW"-Left fork: %p\n" RST, (void *)table->philo[i].fork_l);
		printf(YLW"-Right fork: %p\n" RST, (void *)table->philo[i].fork_r);
		printf(YLW"-Last meal time: %d\n" RST, table->philo[i].t_l_meal);
		printf(YLW"-Number of meals eaten: %d\n" RST, table->philo[i].c_meal);
		printf("\n");
		i++;
	}
	return (0);
}
/*
*/

void	print_err(char *str)
{
	printf(RED "Error: %s\n" RST, str);
}

/*
*/
void	print_death(t_table *table, int i)
{
	table->end = 1;
	pthread_mutex_lock(&(table->print));
	printf("%ld %d %s\n", time_convert() - table->s_time, \
	table->philo[i].id_philo + 1, "died");
}

/*
*/
void	print_status(t_philo *philo, int id, char *str)
{
	printf("IEEEEEEP\n");
	if (philo->table->end == 0)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%ld ", (time_convert() - philo->table->s_time));
		printf("%d ", id);
		printf("%s\n", str);
		pthread_mutex_unlock(&philo->table->print);
	}
}
