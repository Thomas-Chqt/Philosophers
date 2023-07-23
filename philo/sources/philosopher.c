/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 14:43:20 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*phi_rout(void *data);
static void	*time_routine(void *data);

t_philosopher	*create_philos(t_fork *forks)
{
	t_philosopher	*philos;
	t_uint64		i;

	if (forks == NUL)
		return (NUL);
	philos = malloc(sizeof(t_philosopher) * get_gdata().nbr_philo);
	if (philos == NUL)
	{
		delete_forks(forks, get_gdata().nbr_philo);
		return (NUL);
	}
	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		philos[i] = (t_philosopher){.is_thread_created = false, .id = i + 1,
			.forks[1] = forks + i, .last_eat = (t_time)0,
			.eat_left = get_gdata().must_eat, .last_print = (t_time)0};
		if (i == 0)
			philos[i].forks[0] = forks + (get_gdata().nbr_philo - 1);
		else
			philos[i].forks[0] = forks + (i - 1);
		i++;
	}
	return (philos);
}

int	run_philos(t_philosopher *philos)
{
	t_uint64	i;
	t_pthread	time_thread;

	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (pthread_create(&philos->thread, NUL, &phi_rout, (philos + i)) != 0)
			return (1);
		philos[i].is_thread_created = true;
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < get_gdata().nbr_philo)
	{
		if (pthread_create(&philos->thread, NUL, &phi_rout, (philos + i)) != 0)
			return (1);
		philos[i].is_thread_created = true;
		i += 2;
	}
	if (pthread_create(&time_thread, NUL, &time_routine, (void *)philos) != 0)
		return (1);
	pthread_join(time_thread, NUL);
	return (0);
}

int	delete_philos(t_philosopher *philos)
{
	t_uint64	i;

	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (philos[i].is_thread_created == true)
			pthread_detach(philos[i].thread);
		i++;
	}
	free(philos);
	return (0);
}

static void	*phi_rout(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (1)
	{	
		if (take_fork(philo, philo->forks[0]) != 0)
			break ;
		if (take_fork(philo, philo->forks[1]) != 0)
			break ;
		if (eat(philo) != 0)
			break ;
		if (drop_fork(philo->forks[0]) != 0)
			break ;
		if (drop_fork(philo->forks[1]) != 0)
			break ;
		if (philo_sleep(philo) != 0)
			break ;
		if (think(philo) != 0)
			break ;
	}
	return (NUL);
}

static void	*time_routine(void *data)
{
	t_philosopher	*philos;
	t_uint64		i;

	philos = (t_philosopher *)data;
	pthread_mutex_lock(get_gdata().global_mutex);
	while (get_gdata().is_finished == false)
	{
		pthread_mutex_unlock(get_gdata().global_mutex);
		i = -1;
		while (++i < get_gdata().nbr_philo)
		{
			if (time_since(philos[i].last_eat) >= get_gdata().die_time)
			{
				pthread_mutex_lock(get_gdata().global_mutex);
				printf("%lu %lu died\n", (t_uint64)get_time(), philos[i].id);
				set_need_eat_left(0);
				pthread_mutex_unlock(get_gdata().global_mutex);
				return (NUL);
			}
		}
		usleep(2000);
		pthread_mutex_lock(get_gdata().global_mutex);
	}
	pthread_mutex_unlock(get_gdata().global_mutex);
	return (NUL);
}
