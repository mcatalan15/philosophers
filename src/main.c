/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/28 13:35:44 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	This function is used to separate the 3 main functions of the program.
	the initialization of the information, the execution of the program and
	the clearing of the program.
*/

int	philo(char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (init_info(argv, &table))
		return (EXIT_FAILURE);
	// print_struct(&table); // delete
	if (exec_program(&table))
		return (EXIT_FAILURE);
	print_totals(&table); // delete
	clear_program(&table);
	return (0);
}

/*
	This main function is used to check the arguments and do a quick
	parsing of them. If the arguments numbers are correct continues.
	If not return EXIT_FAILURE.
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
		return (print_err(ERROR_NARGS));
}
