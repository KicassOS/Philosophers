/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper < pszleper@student.42.fr >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:35:30 by pszleper          #+#    #+#             */
/*   Updated: 2023/01/09 10:39:15 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# define PHILO_ERROR 42

typedef struct s_philo
{
	pthread_t		*tid;
	pthread_mutex_t	*done_eating;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*funeral;
	struct timeval	*last_eat;
	struct timeval	*time;
	struct s_philo	*next;
	int				index;
	int				total_philo;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meal_nb;
	int				*died;
	int				*done;
}					t_philo;

void	ft_free(t_philo *philo_ptr);
int		ft_atoi(char *str);
long	ft_time(struct timeval *time);
void	ft_sleep(int i);
void	ft_printf(char *str, t_philo *philo);

int		ft_join_all_threads(t_philo *philo_ptr);

int		ft_mutex_destroy(pthread_mutex_t *mutex);
int		ft_destroy_mutexes(pthread_mutex_t *funeral, pthread_mutex_t *done);

void	ft_loop(t_philo *philo);

int		ft_check_args(int argc, char **argv);
int		ft_init_time_left_fork(int argc, char **argv, t_philo *philo);
int		ft_init_philo_forks(t_philo *philo, int num_philos, int *died);
int		ft_init_mutexes(t_philo *philo);
t_philo	*ft_parse(int argc, char **argv, int *died);

void	ft_eat(t_philo *philo);
void	ft_must_eat(t_philo *philo);
void	ft_eat_forever(t_philo *philo);
void	ft_odd_even(t_philo *philo);
void	ft_create_philo(t_philo *philo, int	*done);
#endif
