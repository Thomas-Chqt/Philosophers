/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/19 01:38:07 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_loop(void *data);
static void	*time_loop(void *data);

void	create_philo(t_philo *philo, t_settings settings,
			t_pthread_mutex *fork1, t_pthread_mutex *fork2)
{
	static t_uint64	id = 1;

	philo->settings = settings;
	philo->id = id++;
	philo->fork1 = fork1;
	philo->fork2 = fork2;
	philo->last_eat = settings.start_time;
	philo->eat_count = 0;
	pthread_create(&philo->thread, NUL, &philo_loop, philo);
}

void	start_simulation(t_pthread *time_thread, t_philo *philos, t_settings settings)
{
	void	*loop_datas[2];

	loop_datas[0] = (void *)philos;
	loop_datas[1] = (void *)&settings;
	pthread_create(time_thread, NUL, &time_loop, (void *)loop_datas);
	pthread_join(*time_thread, NUL);
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
		philo->last_eat = get_time();
		usleep(philo->settings.time_eat * 1000);
		philo->eat_count += 1;
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		printf("%lu %d is sleeping\n", ms_since(philo->settings.start_time),  philo->id);
		usleep(philo->settings.time_sleep * 1000);
		printf("%lu %d is thinking\n", ms_since(philo->settings.start_time),  philo->id);
	}
}

static void	*time_loop(void *data)
{
	t_philo		*philos;
	t_settings	settings;
	t_uint64	i;

	philos = (t_philo *)((void **)data)[0];
	settings = *((t_settings *)((void **)data)[1]);
	while (1)
	{
		i = 0;
		while (i < settings.nbr_philosophers)
		{
			if (ms_since(philos[i].last_eat) >= settings.time_die)
			{
				printf("%lu %d died\n", ms_since(settings.start_time),  philos[i].id);
				return NUL;
			}
			if (settings.nbr_eat > 0 && philos[i].eat_count >= settings.nbr_eat)
				return NUL;
			i++;
		}
	}
}