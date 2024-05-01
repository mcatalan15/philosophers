/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:55:09 by mcatalan          #+#    #+#             */
/*   Updated: 2024/05/01 20:40:28 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_num_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
		{
			return (0);
		}
		i++;
	}
	return (1);
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
		if (ft_num_str(argv[i]))
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
			return (print_err(ERROR_ARGV));
	}
	return (0);
}
