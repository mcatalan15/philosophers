/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:26:46 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/14 11:22:11 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	error_ext(char *str)
{
	printf(RED "Error: %s\n" RST, str);
	exit(EXIT_FAILURE);
}

int	error_mtx(t_table	*table)
{
	if (pthread_mutex_lock(&table->death))
		return (1);
	table->end = 1;
	if (pthread_mutex_unlock(&table->death))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	if (str)
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '-')
			error_ext("Negative number.");
		else if (str[i] == '+')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = (str[i] - '0') + (res * 10);
			i++;
			if (res > INT_MAX)
				error_ext("Number too big. Max number is 2147483647."\
				"Included.");
		}
	}
	return (res * neg);
}
