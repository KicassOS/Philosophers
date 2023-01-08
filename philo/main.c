/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:36:19 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/08 04:09:57 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_instructions(void)
{
	printf("Wrong number of arguments\n");
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

/*
  This function checks the arguments
  It checks if the numbers are positive, if there's at least one philosopher
  and if the number of meals is at least one
  The function also handles the cases of there being only one philosopher
  and when time_to_die is 0
  It returns the number of philosophers as an int
*/
int	ft_check_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
	{
		printf("Invalid input parameters\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("Invalid number of meals\n");
		return (0);
	}
	if (ft_atoi(argv[2]) == 0)
	{
		printf("0 1 died\n");
		return (0);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%i 1 died\n", ft_atoi(argv[2]));
		return (0);
	}
	return (1);
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
	if (!ft_check_args(argc, argv))
		return (PHILO_ERROR);
	died = 0;
	done = 0;
	philo = ft_parse(argc, argv, &died);
	if (philo == NULL)
		return (PHILO_ERROR);
	ft_create_philo(philo, &done);
	ft_free(philo);
	return (EXIT_SUCCESS);
}
