/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 05:51:13 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/06 10:27:42 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	mod;
	int	i;

	i = 0;
	mod = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '-')
	{
		mod = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + (*str - '0');
		str++;
	}
	if (*str && (*str < '0' || *str > '9'))
		return (-1);
	return (mod * i);
}

/*
  this function extracts the number of milliseconds from the timeval struct
*/
long	ft_time(struct timeval *time)
{
	long			milliseconds;
	struct timeval	tmp;

	if (gettimeofday(&tmp, 0) == -1)
		return (-1);
	milliseconds = (tmp.tv_sec - time->tv_sec) * 1000;
	milliseconds += (tmp.tv_usec - time->tv_usec) / 1000;
	return (milliseconds);
}

/*
  this function sleeps until i milliseconds 
*/
void	ft_sleep(int i)
{
	struct timeval	tmp;
	int				j;

	if (gettimeofday(&tmp, 0) == -1)
		return ;
	j = 0;
	while (j < i)
	{
		usleep(5);
		j = ft_time(&tmp);
	}
}

/*
  This function prints according to the format, and won't print after
  a philosopher has died
*/
void	ft_printf(char *str, t_philo *philo)
{
	long	i;

	pthread_mutex_lock(philo->funeral);
	i = ft_time(philo->time);
	if (*philo->died)
	{
		pthread_mutex_unlock(philo->funeral);
		return ;
	}
	printf("%lu %i %s\n", i, philo->index, str);
	pthread_mutex_unlock(philo->funeral);
}

void	ft_free(t_philo *philo_ptr)
{
	t_philo	*current_philo;

	pthread_mutex_destroy(philo_ptr->funeral);
	free(philo_ptr->funeral);
	pthread_mutex_destroy(philo_ptr->done_eating);
	free(philo_ptr->done_eating);
	free(philo_ptr->time);
	while (philo_ptr)
	{
		pthread_join(*philo_ptr->tid, 0);
		current_philo = philo_ptr;
		pthread_mutex_destroy(philo_ptr->fork_r);
		free(philo_ptr->fork_r);
		free(philo_ptr->tid);
		free(philo_ptr->last_eat);
		philo_ptr = philo_ptr->next;
		free(current_philo);
	}
}
