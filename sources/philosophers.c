/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 13:01:36 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_loop(void *data);
static void	*time_loop(void *data);

int	setup(int argc, char const *argv[], t_settings *settings)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (atoi_fill(argv[1], &settings->nbr_philo) != 0)
		return (-1);
	if (atoi_fill(argv[2], &settings->time_die) != 0)
		return (-1);
	if (atoi_fill(argv[3], &settings->time_eat) != 0)
		return (-1);
	if (atoi_fill(argv[4], &settings->time_sleep) != 0)
		return (-1);
	settings->nbr_eat = 0;
	if (argc == 6 && atoi_fill(argv[5], &settings->nbr_eat) != 0)
		return (-1);
	settings->srt_time = get_time();
	return (0);
}

void	create_philo(t_philo *philo, t_settings settings,
			t_pthread_mutex *fork1, t_pthread_mutex *fork2)
{
	static t_uint64	id = 1;

	philo->settings = settings;
	philo->id = id++;
	philo->fork1 = fork1;
	philo->fork2 = fork2;
	philo->last_eat = settings.srt_time;
	philo->eat_count = 0;
	pthread_create(&philo->thread, NUL, &philo_loop, philo);
	usleep(100);
}

void	start_simulation(t_pthread *time_thread, t_philo *philos,
			t_settings settings)
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
		printf("%lu %lu has taken a fork\n",
			ms_since(philo->settings.srt_time), philo->id);
		pthread_mutex_lock(philo->fork2);
		printf("%lu %lu has taken a fork\n",
			ms_since(philo->settings.srt_time), philo->id);
		printf("%lu %lu is eating\n", ms_since(philo->settings.srt_time),
			philo->id);
		philo->last_eat = get_time();
		usleep(philo->settings.time_eat * 1000);
		philo->eat_count += 1;
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		printf("%lu %lu is sleeping\n", ms_since(philo->settings.srt_time),
			philo->id);
		usleep(philo->settings.time_sleep * 1000);
		printf("%lu %lu is thinking\n", ms_since(philo->settings.srt_time),
			philo->id);
	}
	return (NUL);
}

static void	*time_loop(void *data)
{
	t_philo		*philos;
	t_settings	set;
	t_uint64	i;

	philos = (t_philo *)((void **)data)[0];
	set = *((t_settings *)((void **)data)[1]);
	while (1)
	{
		i = 0;
		while (i < set.nbr_philo)
		{
			if (ms_since(philos[i].last_eat) >= set.time_die)
				return ((void *)(t_uint64)printf("%lu %lu died\n",
					ms_since(set.srt_time), philos[i].id));
			i++;
		}
		i = 0;
		while ((set.nbr_eat > 0) && (i < set.nbr_philo)
			&& (philos[i].eat_count >= set.nbr_eat))
			i++;
		if (i == set.nbr_philo)
			return (NUL);
	}
	return (NUL);
}
