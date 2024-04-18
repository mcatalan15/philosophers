/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/18 12:11:02 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 */
void	*checker(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (table->m_meals == (table->n_philo * table->m_meals))
			return (NULL);
		if (((time_convert() - table->philo[i].t_l_meal) > table->t_die) && (table->philo[i].c_meal != table->m_meals))
		{
			print_death(table, i); //TO-DO
			break ;
		}
		i++;
	}
	return (NULL);
}

/*
*/
void	*check_status(void *info)
{
	t_table	*table;

	table = (t_table *)info;
	while (table->c_threads != table->n_philo)
		pause_time(1);
	table->s_time = time_convert();
	pause_time(table->t_eat / 2);
	checker(table);
	return (NULL);
}

/*
*/

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_status(philo, philo->id_philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	print_status(philo, philo->id_philo, "has taken a fork");
	print_status(philo, philo->id_philo, "is eating");
	philo->t_l_meal = time_convert();
	if (philo->table->end == 0)
		pause_time(philo->table->t_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (philo->table->m_meals != INT_MAX)
	{
		philo->c_meal++;
		pthread_mutex_lock(&philo->table->meals);
		philo->table->t_meals++;
		pthread_mutex_unlock(&philo->table->meals);
	}
}

/*	
*/

void	*action(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	// pthread_mutex_lock(&philo->table->init); // ??
	philo->table->c_threads++;
	pthread_mutex_unlock(&philo->table->init);
	while (philo->table->s_time == 0)
		pause_time(1);
	philo->t_l_meal = philo->table->s_time;
	if (philo->table->n_philo == 1)
	{
		printf("HOla1\n");
		print_status(philo, philo->id_philo, "Taken fork");
		return (NULL);
	}
	printf("HOla2\n");
	if (philo->id_philo % 2 == 1)
	{
		printf("HOla3\n");
		pause_time(philo->table->t_eat / 2);
	}
	printf("HOla4\n");
	while (philo->table->end == 0 && philo->c_meal < philo->table->m_meals)
	{
		printf("HOla5\n");
		eat(philo);
		print_status(philo, philo->id_philo, "Is sleeping");
		if (philo->table->end == 0)
			pause_time(philo->table->t_sleep);
		print_status(philo, philo->id_philo, "Is thinking");
	}
	printf("HOla6\n");
	return (0);
}

/*
*/

int	exec_program(t_table *table)
{
	int			i;
	pthread_t	*philo;

	i = -1;
	table->philo_t = malloc(sizeof(pthread_t) * (table->n_philo));
	if (!table->philo_t)
	{
		print_err(ERROR_MALLOC);
		return (1);
	}
	philo = table->philo_t;
	pthread_mutex_lock(&table->init); // ??
	while (++i < table->n_philo)
	{
		if (pthread_create(&philo[i], NULL, &action, (void *)&table->philo) != 0)
		{
			print_err("Error creating philo\n");
			return (1);
		}
		if (pthread_detach(philo[i]) != 0)
		{
			print_err("Error detaching philo\n");
			return (1);
		}
		printf("HOLA7\n");
	}
	if (pthread_create(&table->check_d, NULL, &check_status, (void *)table) != 0)
	{
		print_err("error checking death");
		return (1);
	}
	pthread_join(table->check_d, NULL);
	return (0);
}

/*
	philo function is the main function of the program.
	First, it checks if the arguments are valid.
	Then, it initializes the data.
	After that, it executes the program.
	Finally, it destroys the data.
*/

int	philo(char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (init_data(&table, argv))
		return (EXIT_FAILURE);
	//print_struct(&table);
	if (exec_program(&table))
		return (EXIT_FAILURE);
	clear_program(&table); //-> TO COMPLETE
	return (0);
}

/*
	Filter for argc. Philo needs 5 or 6 arguments.
	./philo 5 800 200 200 [optional: 7]
	./philo philos time_to_die time_to_eat time_to_sleep [optional: max_meals]
*/

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (parsing(argv))
			return (EXIT_FAILURE);
		else
		{
			if (philo(argv))
				return (EXIT_FAILURE);
		}
	}
	else
	{
		print_err("Wrong args.\n\tPhilo needs 5 or 6 arguments");
		return (EXIT_FAILURE);
	}
	return (0);
}

