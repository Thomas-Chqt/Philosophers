/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:06:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:27:36 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_philosopher *philo, t_fork *fork)
{
	pthread_mutex_lock(fork);
	printf("%lu %lu has taken a fork\n", (t_uint64)get_time(), philo->id);
	return (0);
}

int	eat(t_philosopher *philo)
{
	t_time	eat_time;

	eat_time = get_time();
	printf("%lu %lu is eating\n", (t_uint64)eat_time, philo->id);
	philo->last_eat = (t_uint64)eat_time;
	usleep(get_setting(e_eat_time) * 1000);
	philo->eat_count += 1;
	return (0);
}

int	drop_fork(t_fork *fork)
{
	pthread_mutex_unlock(fork);
	return (0);
}

int	philo_sleep(t_philosopher *philo)
{
	printf("%lu %lu is sleeping\n", (t_uint64)get_time(), philo->id);
	usleep(get_setting(e_sleep_time) * 1000);
	return (0);
}

int	think(t_philosopher *philo)
{
	printf("%lu %lu is thinking\n", (t_uint64)get_time(), philo->id);
	return (0);
}
