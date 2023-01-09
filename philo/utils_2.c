/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:55:54 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/09 05:11:09 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
  This function joins all threads, checking for errors
*/
int	ft_join_all_threads(t_philo *philo_ptr)
{
	while (philo_ptr)
	{
		if (pthread_join(*philo_ptr->tid, NULL) != 0)
			return (0);
		philo_ptr = philo_ptr->next;
	}
	return (1);
}
