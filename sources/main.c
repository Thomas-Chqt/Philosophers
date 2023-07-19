/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/19 01:31:39 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char const *argv[])
{
	t_settings		settings = {.nbr_philosophers = 10, .time_die = 5000, .time_eat = 1000, .time_sleep = 500};
	t_pthread		time_thread;
	t_pthread_mutex	*forks;
	t_philo			*philos;
	t_uint64		i;

	settings.start_time = get_time();
	forks = malloc(sizeof(t_pthread_mutex) * settings.nbr_philosophers);
	philos = malloc(sizeof(t_philo) * settings.nbr_philosophers);
	if (forks == NUL || philos == NUL)
	{
		free(forks);
		free(philos);
		return (printf("Malloc Error\n"));
	}
	i = 0;
	while (i < settings.nbr_philosophers)
		pthread_mutex_init(forks + (i++), NUL);
	create_philo(philos, settings, forks + (settings.nbr_philosophers - 1), forks);
	i = 0;
	usleep(1000);
	while (++i < settings.nbr_philosophers)
	{
		create_philo(philos + i, settings, forks + (i - 1), forks + i);
		usleep(1000);
	}
	start_simulation(&time_thread, philos, settings);
	return (0);
}
