/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/13 10:59:41 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_ext(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}

int	parsing(char **argv)
{
	for (int i = 0; argv[i]; i++)
		printf("argv %d: %s\n", i, argv[i]);
	return (0);
}

int	exec_philo(char **argv)
{
	if (parsing(argv) == -1)
		error_ext("Check arguments. Too long or not int");
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		exec_philo(argv);
	else
		error_ext("Wrong args. Philo needs 5 or 6 arguments");
	return (0);
}
