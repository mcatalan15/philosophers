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

/*	
*/

int	philo_action(t_philo *philo)
{
	(void)philo;
	return (0);
}

/*
*/

int	exec_program(t_table *table)
{
	(void)table;
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

