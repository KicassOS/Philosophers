/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 05:51:08 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/06 06:14:40 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
  This function loops through all philosophers infinitely unless the
  number of meals each philosopher must eat was given.
  In the loop, we compare last_eat to death_time for each philosopher,
  if the former is bigger than the latter, then our philosopher died.
  The funeral mutex gets locked, message gets printed and program ends.
*/
void	ft_death(t_philo *philo)
{
	t_philo	*temp;
	int		j;
	long	i;

	temp = philo;
	while (*philo->done < philo->total_philo)
	{
		j = ft_time(philo->last_eat);
		if (j >= philo->death_time)
		{
			*philo->died = 1;
			i = ft_time(philo->time);
			printf("%lu %i died\n", i, philo->index);
			return ;
		}
		philo = philo->next;
		if (philo == NULL)
			philo = temp;
	}
}
