/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 01:44:45 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philospher_routine(void *data);

t_philosopher	*create_philos(t_fork *forks)
{
	t_philosopher	*philos;
	t_uint64		i;

	philos = malloc(sizeof(t_philosopher) * get_gdata().nbr_philo);
	if (philos == NUL)
		return (NUL);
	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		philos[i].is_thread_created = false;
		philos[i].id = i + 1;
		if (i == 0)
			philos[i].forks[0] = forks + (get_gdata().nbr_philo - 1);
		else
			philos[i].forks[0] = forks + (i - 1);
		philos[i].forks[1] = forks + i;
		philos[i].last_eat = (t_time)0;
		philos[i].eat_left = get_gdata().must_eat;
		i++;
	}
	return (philos);
}

int	run_philos(t_philosopher *philos)
{
	t_uint64	i;

	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (pthread_create(&philos->thread, NUL, &philospher_routine, (void *)(philos + i)) != 0)
			return (1);
		philos[i].is_thread_created = true;
		i++;
	}
	return (0);
}

int	delete_philos(t_philosopher *philos)
{
	t_uint64	i;
	int			ret_val;

	ret_val = 0;
	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (philos[i].is_thread_created == true)
		{
			if (pthread_join(philos[i].thread, NUL) != 0)
				ret_val = 1;
		}
		i++;
	}
	free(philos);
	return (ret_val);
}

static void	*philospher_routine(void *data)
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
