/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 05:51:13 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/06 01:54:14 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo_ptr)
{
	t_philo	*current_philo;

	pthread_mutex_unlock(philo_ptr->funeral);
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

void	ft_sleep(int i)
{
	struct timeval	tmp;
	int				j;

	if (gettimeofday(&tmp, 0) == -1)
		return ;
	j = 0;
	while (j < i)
	{
		usleep(200);
		j = ft_time(&tmp);
	}
}

void	ft_printf(char *str, t_philo *data)
{
	long	i;

	pthread_mutex_lock(data->funeral);
	i = ft_time(data->time);
	if (*data->died)
	{
		pthread_mutex_unlock(data->funeral);
		return ;
	}
	printf("%lu %i %s\n", i, data->index, str);
	pthread_mutex_unlock(data->funeral);
}
