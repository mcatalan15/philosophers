/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/14 20:49:17 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parsing(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if ((ft_atoi(argv[i])) > INT_MAX)
			error_ext("Number too big. Max number is 2147483648.");
		else if ((ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > 200) && i == 1)
			error_ext("Number of philosophers must be between 0 and 200."\
			"Both excluded.");
		else if ((ft_atoi(argv[i]) < 60 || ft_atoi(argv[i]) > INT_MAX - 1)
			&& (i > 1 && i < 5))
			error_ext("Times need to be between 60ms and 2147483647ms."\
			"Both included.");
		else if ((ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > INT_MAX - 1)
			&& i == 5)
			error_ext("Number of meals must be between 1 and 2147483647."\
			"Both included.");
		// need to check if there are only numbers or plus/minus signs
	}
	return (0);
}

int	philo_action(t_philo *philo)
{
	(void)philo;
	return (0);
}

/*
	
*/

int	exec_program(t_table *table)
{
	// (void)table;
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_action, &table->philo[i]))
			error_ext("Error: Thread creation failed");
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			error_ext("Error: Thread join failed");
		i++;
	}
	return (0);
}

/*
	philo function is the main function of the program.
	First, it checks if the arguments are valid.
	Then, it initializes the data.
	After that, it executes the program.
	Finally, it destroys the data.
*/

int	philo(int argc, char **argv)
{
	t_table	table;

	(void)argc;
	memset(&table, 0, sizeof(t_table));
	if (parsing(argv))
		return (EXIT_FAILURE);
	init_data(&table, argv);
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
		philo(argc, argv);
	else
		error_ext("Wrong args.\n\tPhilo needs 5 or 6 arguments");
	return (0);
}
