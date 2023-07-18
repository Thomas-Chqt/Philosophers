/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/18 13:38:53 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_loop(void *data);

void	create_philo(t_philo *philo, t_settings settings,
			t_pthread_mutex *fork1, t_pthread_mutex *fork2)
{
	static t_uint64	id = 1;

	philo->settings = settings;
	philo->id = id++;
	philo->fork1 = fork1;
	philo->fork2 = fork2;
	philo->last_eat = settings.start_time;
	pthread_create(&philo->thread, NUL, &philo_loop, philo);
}

static void	*philo_loop(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(philo->fork1);
		printf("%lu %d has taken a fork\n", ms_since(philo->settings.start_time),  philo->id);
		pthread_mutex_lock(philo->fork2);
		printf("%lu %d has taken a fork\n", ms_since(philo->settings.start_time),  philo->id);
		printf("%lu %d is eating\n", ms_since(philo->settings.start_time),  philo->id);
		usleep(philo->settings.time_eat * 1000);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		printf("%lu %d is sleeping\n", ms_since(philo->settings.start_time),  philo->id);
		usleep(philo->settings.time_sleep * 1000);
		printf("%lu %d is thinking\n", ms_since(philo->settings.start_time),  philo->id);
	}
}
