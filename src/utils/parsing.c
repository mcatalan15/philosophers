/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:09 by mcatalan          #+#    #+#             */
/*   Updated: 2024/04/18 11:55:26 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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