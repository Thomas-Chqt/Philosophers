/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/22 19:23:03 by tchoquet         ###   ########.fr       */
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
		if (create_philo(philos + i, i + 1) != 0)
			return (delete_philos(philos, i + 1));
		philos[i].id = i + 1;
		if (i = 0)
			philos[i].forks[0] = forks + (get_gdata().nbr_philo - 1);
		else
			philos[i].forks[0] = forks + (i - 1);
		philos[i].forks[1] = forks + i;
		philos[i].last_eat = (t_time)0;
		philos[i].eat_count = 0;
		i++;
	}
	return (philos);
}

void	*delete_philos(t_philosopher *philos, t_uint64 count)
{
	t_uint64	i;

	i = 0;
	while (i < count)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
	free(philos);
	return (NUL);
}

int	run_philos(t_philosopher *philos)
{
	t_uint64	i;

	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (pthread_create(&philos->thread, NUL, &philospher_routine, (void *)(philos + i)) != 0)
			return (1);
	}
	
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
