/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 05:51:11 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/09 03:35:58 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
  This function makes a philosopher eat.
  It locks the forks, printing the messages, and after picking both
  the forks up it eats for ft_sleep(eat_time) milliseconds
*/
void	ft_eat(t_philo *philo)
{
	if (*philo->died)
		return ;
	pthread_mutex_lock(philo->fork_r);
	ft_printf("has taken a fork", philo);
	if (*philo->died)
	{
		pthread_mutex_unlock(philo->fork_r);
		return ;
	}
	pthread_mutex_lock(philo->fork_l);
	ft_printf("has taken a fork", philo);
	if (gettimeofday(philo->last_eat, 0))
		return ;
	if (*philo->died)
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return ;
	}
	ft_printf("is eating", philo);
	ft_sleep(philo->eat_time);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

/*
  This function is called when the optional parameter
  (number of meals AKA meal_nb) is given,
  and keeps looping until all philosophers haven't eaten all their meals
  When they're all done, we lock the done_eating mutex and increase it by one
*/
void	ft_meal_nb(t_philo *philo)
{
	while (philo->meal_nb)
	{
		ft_eat(philo);
		if (*philo->died)
			return ;
		philo->meal_nb--;
		if (philo->meal_nb == 0)
		{
			pthread_mutex_lock(philo->done_eating);
			*philo->done += 1;
			pthread_mutex_unlock(philo->done_eating);
			return ;
		}
		ft_printf("is sleeping", philo);
		ft_sleep(philo->sleep_time);
		ft_printf("is thinking", philo);
	}
}

/*
  This function is called when the optional parameter is absent
  It will keep the philosophers working until one of them dies
  (his died value becomes equal to 1).
*/
void	ft_eat_forever(t_philo *philo)
{
	while (*philo->died == 0)
	{
		ft_eat(philo);
		ft_printf("is sleeping", philo);
		if (*philo->died)
			return ;
		ft_sleep(philo->sleep_time);
		ft_printf("is thinking", philo);
	}
}

/*
  This function is the core of the solution to the problem: it makes the
  odd-numbered philosophers wait for eat_time in order to
  let the even-numbered philosophers eat, thus preventing a deadlock
  where each philosopher would pick up their right fork at the start
  and they would all starve together while holding only one fork
*/
void	ft_odd_even(t_philo *philo)
{
	if (philo->index % 2 != 0)
		usleep(philo->eat_time * 1000);
	if (philo->meal_nb)
		ft_meal_nb(philo);
	else
		ft_eat_forever(philo);
}

/*
  This function creates as many threads as there are philosophers
  and initializes some of their values
*/
void	ft_create_philo(t_philo *philo, int	*done)
{
	t_philo			*tmp;
	struct timeval	*time1;

	time1 = malloc(sizeof(struct timeval));
	if (!time1 || gettimeofday(time1, 0) == -1)
		return ;
	tmp = philo;
	while (tmp)
	{
		tmp->done = done;
		tmp->time = time1;
		tmp->last_eat = malloc(sizeof(struct timeval));
		if (!tmp->last_eat || gettimeofday(tmp->last_eat, 0) == -1)
			return ;
		tmp->tid = malloc(sizeof(pthread_t));
		if (!tmp->tid)
			return ;
		if (pthread_create(tmp->tid, 0, (void *)&ft_odd_even, (void *)tmp))
			return ;
		tmp = tmp->next;
	}
	ft_loop(philo);
}
