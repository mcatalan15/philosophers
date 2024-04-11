/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/11 11:51:24 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parsing(char **argv)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (argv[i])
	{
		if (str_validator(argv[i]) == 1)
			return (-1);
		i++;
	}
	i = 0;
	while (++i < 6)
	{
		num = ft_atoi(argv[i]);
		if ((i == 1 || i == 5) && num < 1)
			error_ext("Error: Number of philosophers and/or number of meals must be bigger than 0.");
		if (i == 1 && num >= 200)
			error_ext("Error: Number of philosophers must be less than 200.");
		if ((i > 1 && i < 5) && num < 60)
			error_ext("Error: Times need to be bigger than 60ms.\n"
				"\tCheck time_to_die, time_to_eat and time_to_sleep");
		printf("num: %d\n", num);
	}
	return (0);
}

// void	*loop(void *arg) // t_philo
// {
// 	pthread_mutex_lock(init);
// }

/*
	exec_program function is used to execute the main program after all is
	set up.
*/

// int	exec_program(t_table *table)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < table->n_philo)
// 	{
// 		if (pthread_create(&table->philo[i].id_thread, NULL, &loop , ) != 0)
// 			error_ext("Failed to create threads");
// 		else
// 			printf("Philo %d created\n", i);
// 	}
// 	printf("creation finished\n");
// 	// i = -1;
// 	// while (&table->philo[++i])
// 	// {
		
// 	// }
// 	// pthread_mutex_destroy();
// 	return (0);
// }

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

	if (parsing(argv) == -1)
		error_ext("Check arguments.\n \tToo long, not int or negative num");
	init_data(&table, argv);
	print_struct(&table);
	// exec_program(&table);
	clear_program(&table);
	printf("iep\n");
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
		philo(argv);
	else
		error_ext("Wrong args.\n\tPhilo needs 5 or 6 arguments");
	return (0);
}
