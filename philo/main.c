/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:36:19 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/06 05:24:29 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_instructions(void)
{
	printf("Wrong number of arguments\n");
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		died;
	int		done;

	if (argc != 5 && argc != 6)
	{
		ft_print_instructions();
		return (PHILO_ERROR);
	}
	died = 0;
	done = 0;
	philo = ft_parse(argc, argv, &died);
	if (philo == NULL)
		return (PHILO_ERROR);
	ft_create_philo(philo, &done);
	ft_free(philo);
	return (EXIT_SUCCESS);
}
