/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/19 16:32:39 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_return(void *ptr1, void *ptr2, char const *msg);

int	main(int argc, char const *argv[])
{
	t_settings		settings;
	t_pthread		time_thread;
	t_pthread_mutex	*forks;
	t_philo			*philos;
	t_uint64		i;

	if (setup(argc, argv, &settings) != 0)
		return (free_return(NUL, NUL, "Arg error\n"));
	forks = malloc(sizeof(t_pthread_mutex) * settings.nbr_philo);
	philos = malloc(sizeof(t_philo) * settings.nbr_philo);
	if (forks == NUL || philos == NUL)
		return (free_return(forks, philos, "Malloc error\n"));
	i = 0;
	while (i < settings.nbr_philo)
		pthread_mutex_init(forks + (i++), NUL);
	create_philo(philos, settings, forks + (settings.nbr_philo - 1), forks);
	i = 0;
	while (++i < settings.nbr_philo)
		create_philo(philos + i, settings, forks + (i - 1), forks + i);
	start_simulation(&time_thread, philos, settings);
	free(philos);
	free(forks);
	return (0);
}

int	free_return(void *ptr1, void *ptr2, char const *msg)
{
	free(ptr1);
	free(ptr2);
	printf("%s", msg);
	return (-1);
}
