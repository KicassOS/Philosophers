/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:00:44 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/08 04:11:08 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
  This function iterates through philosophers and keeps initializing values
  Most importantly, it gives them their left fork
*/
int	ft_part_two(int argc, char **argv, t_philo *philo)
{
	t_philo			*temp;
	t_philo			*temp2;

	temp2 = philo;
	while (temp2)
	{
		temp = temp2->next;
		temp2->death_time = ft_atoi(argv[2]);
		temp2->eat_time = ft_atoi(argv[3]);
		temp2->sleep_time = ft_atoi(argv[4]);
		temp2->meal_nb = 0;
		if (argc == 6)
			temp2->meal_nb = ft_atoi(argv[5]);
		if (temp == NULL)
			temp2->fork_l = philo->fork_r;
		else
			temp2->fork_l = temp->fork_r;
		temp2 = temp2->next;
	}
	return (0);
}

/*
  This function creates as many forks as there are philosophers
  It assigns it as a right fork to all, but that will be fixed
  in ft_part_two
*/
int	ft_part_one(t_philo *philo, int k, int *died)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (k > i++)
	{
		philo->total_philo = k;
		philo->died = died;
		philo->index = i;
		philo->next = NULL;
		philo->fork_r = malloc(sizeof(pthread_mutex_t));
		if (!philo->fork_r || pthread_mutex_init(philo->fork_r, NULL))
			return (1);
		if (k == i)
			break ;
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return (1);
		philo->next = tmp;
		philo = tmp;
	}
	return (0);
}

/*
  This function creates 2 mutexes:
  one for done_eating and another for the funeral
  Done_eating is for counting the philosophers who ate the assigned
  number of meals and can now stop
  Done_eating is here to prevent the data race that would occur
  if 2 philosophers finished eating around the same time
  Funeral is used to tell philosophers one of them has died
  and that we can stop the program
  Without the funeral mutex some messages would still be printed out
  after the first death
*/
int	ft_part_three(t_philo *philo)
{
	pthread_mutex_t		*funeral;
	pthread_mutex_t		*done_eating;

	funeral = malloc(sizeof(pthread_mutex_t));
	if (!funeral || pthread_mutex_init(funeral, NULL))
		return (1);
	done_eating = malloc(sizeof(pthread_mutex_t));
	if (!done_eating || pthread_mutex_init(done_eating, NULL))
		return (1);
	while (philo)
	{
		philo->done_eating = done_eating;
		philo->funeral = funeral;
		philo = philo->next;
	}
	return (0);
}

/*
	This function handles the parsing and returns the list of philosophers
*/
t_philo	*ft_parse(int argc, char **argv, int *died)
{
	int		k;
	t_philo	*philo;

	k = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (ft_part_one(philo, k, died))
	{
		ft_free(philo);
		return (NULL);
	}
	if (ft_part_two(argc, argv, philo))
	{
		ft_free(philo);
		return (NULL);
	}
	if (ft_part_three(philo))
	{
		ft_free(philo);
		return (NULL);
	}
	return (philo);
}
