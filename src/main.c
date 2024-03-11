/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:05 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/03/10 14:44:22 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	int	number_of_philosophers = ft_atoi(argv[1]);
	int	time_to_die = ft_atoi(argv[2]);
	int	time_to_eat = ft_atoi(argv[3]);
	int	time_to_sleep = ft_atoi(argv[4]);
	int number_of_times_each_philosopher_must_eat;

		if (argc == 6)
			number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	printf("number_of_philosophers:	%d\n", number_of_philosophers);
	printf("time_to_die:	%d\n", time_to_die);
	printf("time_to_eat:	%d\n", time_to_eat);
	printf("time_to_sleep:	%d\n", time_to_sleep);

	if (argc == 6)
		printf("number_of_times_each_philosopher_must_eat:	%d\n", number_of_times_each_philosopher_must_eat);
	return (0);
}
