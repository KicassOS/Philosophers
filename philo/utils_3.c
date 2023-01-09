/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:29:40 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/09 09:49:38 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
  Destroys a mutex, returns 1 if the destruction succeeded
  Returns 0 if the destruction failed
*/
int	ft_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
		return (0);
	return (1);
}

/*
  Destroys the funeral and done_eating mutexes
  Returns 1 on success for both, 0 if one destruction failed
*/
int	ft_destroy_mutexes(pthread_mutex_t *funeral, pthread_mutex_t *done_eating)
{
	if (!ft_mutex_destroy(funeral))
	{
		printf("Failed to destroy funeral mutex\n");
		return (0);
	}
	if (!ft_mutex_destroy(done_eating))
	{
		printf("Failed to destroy done_eating mutex\n");
		return (0);
	}
	return (1);
}
