/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/16 10:54:14 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parsing2(char **argv, int i)
{
	if ((ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > INT_MAX - 1) && i == 5)
	{
		print_err("Numer of meals worng\n\tMust be between 1 and"\
			" 2147483647. Both included.");
		return (EXIT_FAILURE);
	}
	 // need to check if there are only numbers or plus/minus signs
	return (0);
}

int	parsing(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if ((ft_atoi(argv[i])) > INT_MAX)
		{
			print_err("Number too big.\n\tMax number is 2147483648.");
			return (EXIT_FAILURE);
		}
		else if ((ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200) && i == 1)
		{
			print_err("Number of philosophers wrong\n\t"\
				"Must be between 0 and 200. Both excluded.");
			return (EXIT_FAILURE);
		}
		else if ((ft_atoi(argv[i]) < 60 || ft_atoi(argv[i]) > INT_MAX - 1)
			&& (i > 1 && i < 5))
		{
			print_err("Time wrong\n\tTime need to be between 60ms and"\
				" 2147483647ms. Both included.");
			return (EXIT_FAILURE);
		}
		else if (parsing2(argv, i))
			return (EXIT_FAILURE);
	}
	return (0);
}

long	time_convert(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	pause_time(long wait_time)
{
	long start;

	start = time_convert();
	usleep(wait_time * 850); //Porq 850?
	while (time_convert() - start < wait_time)
		usleep(wait_time * 6); //Porq 6?
}

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
void	print_status(t_philo *philo, int id, char *str)
{
	if (philo->table->death == 0)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%ld ", (time_convert() - philo->table->s_time));
		printf("%d ", id);
		printf("%s\n", str);
		pthread_mutex_unlock(&philo->table->print);
	}
}

/*
*/
int	*check_status(void *info)
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
	pthread_mutex_lock(&philo->table->init);
	philo->table->c_threads++;
	pthread_mutex_unlock(&philo->table->init);
	while (philo->table->s_time == 0)
		pause_time(1);
	philo->t_l_meal = philo->table->s_time;
	if (philo->table->n_philo == 1)
	{
		print_status(philo, philo->id_philo, "Taken fork");
		return (NULL);
	}
	if (philo->id_philo % 2 == 1)
		pause_time(philo->table->t_eat / 2);
	while (philo->table->end == 0 && philo->c_meal < philo->table->m_meals)
	{
		eat(philo);
		print_status(philo, philo->id_philo, "Is sleeping");
		if (philo->table->end == 0)
			pause_time(philo->table->t_sleep);
		print_status(philo, philo->id_philo, "Is thinking");
	}
	return (0);
}

/*
*/

int	exec_program(t_table *table)
{
	int		i;
	pthread_t	*philo;

	i = 0;
	table->philo_t = malloc(sizeof(pthread_t) * (table->n_philo));
	if (!table->philo_t)
	{
		print_err(ERROR_MALLOC);
		return (1);
	}
	philo = table->philo_t;
	while (i < table->n_philo)
	{
		if (pthread_create(&philo[i], NULL, &action, (void *)&table->philo)!= 0)
		{
			print_err("Error creating philo\n");
			return (1);
		}
		if (pthread_detach(philo[i]) != 0)
		{
			print_err("Error detaching philo\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&table->end, NULL, &check_status, (void *)table) != 0)
	{
		print_err("error checking death");
		return (1);
	}
	pthread_join(table->end, NULL);
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
	print_struct(&table);
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

