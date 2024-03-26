/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/26 11:04:00 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_ext(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	parsing(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("argv %d: %s\n", i, argv[i]);
		i++;
	}
	return (0);
}

int	philo(char **argv)
{
	if (parsing(argv) == -1)
		error_ext("Check arguments. Too long or not int");
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		philo(argv);
	else
		error_ext("Wrong args. Philo needs 5 or 6 arguments");
	return (0);
}