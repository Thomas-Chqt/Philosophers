/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:32:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_philo(t_philosopher *philo, t_uint64 id);
static void	*philospher_routine(void *data);

t_philosopher	*create_philos(void)
{
	t_philosopher	*philos;
	t_uint64		i;

	if (init_forks() != 0)
		return (NUL);
	philos = malloc(sizeof(t_philosopher) * get_setting(e_nbr_philo));
	if (philos == NUL)
		return (delete_forks());
	i = 0;
	while (i < get_setting(e_nbr_philo))
	{
		if (create_philo(philos + i, i + 1) != 0)
			return (delete_philos(philos, i + 1));
		usleep(10);
		i += 2;
		if (i % 2 == 0 && i >= get_setting(e_nbr_philo))
			i = 1;
	}
	return (philos);
}

void	*delete_philos(t_philosopher *philos, t_uint64 count)
{
	t_uint64	i;

	delete_forks();
	i = 0;
	while (i < count)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
	free(philos);
	return (NUL);
}

static int	create_philo(t_philosopher *philo, t_uint64 id)
{
	philo->id = id;
	if (id == 1)
		philo->forks[0] = get_forks() + (get_setting(e_nbr_philo) - 1);
	else
		philo->forks[0] = get_forks() + (id - 2);
	philo->forks[1] = get_forks() + (id - 1);
	philo->last_eat = (t_time)0;
	philo->eat_count = 0;
	if (pthread_create(&philo->thread, NUL, &philospher_routine, philo) != 0)
		return (1);
	return (0);
}

static void	*philospher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (1)
	{	
		if (take_fork(philo, philo->forks[0]) != 0)
			return (NUL);
		if (take_fork(philo, philo->forks[1]) != 0)
			return (NUL);
		if (eat(philo) != 0)
			return (NUL);
		if (drop_fork(philo->forks[0]) != 0)
			return (NUL);
		if (drop_fork(philo->forks[1]) != 0)
			return (NUL);
		if (philo_sleep(philo) != 0)
			return (NUL);
		if (think(philo) != 0)
			return (NUL);
	}
	return (NUL);
}
