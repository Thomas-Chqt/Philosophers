/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:04:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:25:16 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*time_routine(void *data);

int	run_simulation(t_philosopher *philos)
{
	t_pthread	thread;

	if (pthread_create(&thread, NUL, &time_routine, (void *)philos) != 0)
	{
		delete_philos(philos, get_setting(e_nbr_philo));
		return (1);
	}
	if (pthread_join(thread, NUL) != 0)
	{
		delete_philos(philos, get_setting(e_nbr_philo));
		return (2);
	}
	return (0);
}

static void	*time_routine(void *data)
{
	t_philosopher	*philos;
	t_uint64		i;

	philos = (t_philosopher *)data;
	while (1)
	{
		i = 0;
		while (i < get_setting(e_nbr_philo))
		{
			if (time_since(philos[i].last_eat) >= get_setting(e_die_time))
			{
				printf("%lu %lu died\n", get_time(), philos[i].id);
				return (NUL);
			}
			i++;
		}
		i = 0;
		while ((get_setting(e_must_eat) > 0) && (i < get_setting(e_nbr_philo))
			&& (philos[i].eat_count >= get_setting(e_must_eat)))
			i++;
		if (i == get_setting(e_nbr_philo))
			return (NUL);
	}
	return (NUL);
}
