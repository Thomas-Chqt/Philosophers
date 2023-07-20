/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 17:19:05 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philospher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (1)
	{
		pthread_mutex_lock(philo->forks[0]);
		printf("%lu %lu has taken a fork\n", get_time_ms(), philo->id);
		pthread_mutex_lock(philo->forks[1]);
		printf("%lu %lu has taken a fork\n", get_time_ms(), philo->id);
		printf("%lu %lu is eating\n", get_time_ms(), philo->id);
		philo->last_eat = get_time();
		usleep(get_eat_time() * 1000);
		philo->eat_count += 1;
		pthread_mutex_unlock(philo->forks[0]);
		pthread_mutex_unlock(philo->forks[1]);
		printf("%lu %lu is sleeping\n", get_time_ms(), philo->id);
		usleep(get_sleep_time() * 1000);
		printf("%lu %lu is thinking\n", get_time_ms(), philo->id);
	}
	return (NUL);
}

void	*time_routine(void *data)
{
	t_philosopher	*philos;
	t_uint64		i;

	philos = (t_philosopher *)data;
	while (1)
	{
		i = 0;
		while (i < get_nbr_philo())
		{
			if (ms_since(philos[i].last_eat) >= get_die_time())
			{
				printf("%lu %lu died\n", get_time_ms(), philos[i].id);
				return (NUL);
			}
			i++;
		}
		i = 0;
		while ((get_must_eat() > 0) && (i < get_nbr_philo())
			&& (philos[i].eat_count >= get_must_eat()))
			i++;
		if (i == get_nbr_philo())
			return (NUL);
	}
	return (NUL);
}
