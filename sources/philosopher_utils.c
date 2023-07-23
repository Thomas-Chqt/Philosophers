/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:06:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 14:19:11 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_philosopher *philo, t_fork *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(get_gdata().global_mutex);
	if (get_gdata().is_finished == true)
	{
		pthread_mutex_unlock(get_gdata().global_mutex);
		return (1);
	}
	printf("%lu %lu has taken a fork\n", (t_uint64)get_time(), philo->id);
	philo->last_print = (t_uint64)get_time();
	pthread_mutex_unlock(get_gdata().global_mutex);
	return (0);
}

int	eat(t_philosopher *philo)
{
	t_time	eat_time;

	pthread_mutex_lock(get_gdata().global_mutex);
	if (get_gdata().is_finished == true)
	{
		pthread_mutex_unlock(get_gdata().global_mutex);
		return (1);
	}
	eat_time = philo->last_print;
	printf("%lu %lu is eating\n", (t_uint64)eat_time, philo->id);
	pthread_mutex_unlock(get_gdata().global_mutex);
	philo->last_eat = (t_uint64)eat_time;
	usleep((t_uint64)get_gdata().eat_time * 1000);
	pthread_mutex_lock(get_gdata().global_mutex);
	if (philo->eat_left > 0)
	{
		philo->eat_left -= 1;
		if (philo->eat_left == 0)
			set_need_eat_left(get_gdata().need_eat_left - 1);
	}
	pthread_mutex_unlock(get_gdata().global_mutex);
	return (0);
}

int	drop_fork(t_fork *fork)
{
	pthread_mutex_unlock(fork);
	return (0);
}

int	philo_sleep(t_philosopher *philo)
{
	t_time	sleep_time;

	pthread_mutex_lock(get_gdata().global_mutex);
	if (get_gdata().is_finished == true)
	{
		pthread_mutex_unlock(get_gdata().global_mutex);
		return (1);
	}
	sleep_time = philo->last_print + get_gdata().eat_time;
	printf("%lu %lu is sleeping\n", sleep_time, philo->id);
	philo->last_print = sleep_time;
	pthread_mutex_unlock(get_gdata().global_mutex);
	usleep((t_uint64)get_gdata().sleep_time * 1000);
	return (0);
}

int	think(t_philosopher *philo)
{
	t_time	think_time;

	pthread_mutex_lock(get_gdata().global_mutex);
	if (get_gdata().is_finished == true)
	{
		pthread_mutex_unlock(get_gdata().global_mutex);
		return (1);
	}
	think_time = philo->last_print + get_gdata().sleep_time;
	printf("%lu %lu is thinking\n", think_time, philo->id);
	philo->last_print = think_time;
	pthread_mutex_unlock(get_gdata().global_mutex);
	return (0);
}
