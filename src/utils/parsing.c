/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:09 by mcatalan          #+#    #+#             */
/*   Updated: 2024/05/01 10:48:46 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 0 && str[i] <= 9)
			i++;
		else
			return (EXIT_FAILURE);
	}
	return (0);
}

/*
	This is the second part of the main parsing function. Just checks the
	values of the number of meals. If the value is not between 1 and INT_MAX
	returns EXIT_FAILURE.
*/

int	parsing2(char **argv, int i)
{
	if ((ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > INT_MAX) && i == 5)
		return (print_err(ERROR_NMEALS));
	return (0);
}

/*
	This function is used to check the arguments passed to the program.
	Each argument has a range of values that can be accepted. If the
	arguments are not in the correct range, the function returns EXIT_FAILURE.
*/

int	parsing(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_is_digit(argv[i]) == 0)
		{
			if ((ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > 200) && i == 1)
				return (print_err(ERROR_NPHILO));
			else if ((ft_atol(argv[i]) < 60 || ft_atol(argv[i]) > INT_MAX)
				&& (i > 1 && i < 5))
				return (print_err(ERROR_NTIME));
			else if (parsing2(argv, i))
				return (EXIT_FAILURE);
		}
		else
			return (EXIT_FAILURE);
	}
	return (0);
}
