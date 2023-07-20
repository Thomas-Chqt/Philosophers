/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:25:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 17:23:57 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_uint64	get_nbr_philo_intern(t_uint64 set_val);
t_uint64	get_die_time_intern(t_uint64 set_val);
t_uint64	get_eat_time_intern(t_uint64 set_val);
t_uint64	get_sleep_time_intern(t_uint64 set_val);
t_uint64	get_must_eat_intern(t_uint64 set_val);

int	init_settings(int argc, char const *argv[])
{
	t_uint64	nbr_philo;
	t_uint64	die_time;
	t_uint64	eat_time;
	t_uint64	sleep_time;
	t_uint64	must_eat;

	if (argc < 5 || argc > 6)
		return (-1);
	if (atoi_fill(argv[1], &nbr_philo) != 0)
		return (-1);
	if (atoi_fill(argv[2], &die_time) != 0)
		return (-1);
	if (atoi_fill(argv[3], &eat_time) != 0)
		return (-1);
	if (atoi_fill(argv[4], &sleep_time) != 0)
		return (-1);
	if (argc == 6 && atoi_fill(argv[5], &must_eat) != 0)
		return (-1);
	get_nbr_philo_intern(nbr_philo);
	get_die_time_intern(die_time);
	get_eat_time_intern(eat_time);
	get_sleep_time_intern(sleep_time);
	get_must_eat_intern(must_eat);
	return (0);
}

t_philosopher	*create_philos(void)
{
	t_philosopher	*philos;
	t_uint64		i;

	if (get_forks() == NUL)
		return (NUL);
	philos = malloc(sizeof(t_philosopher) * get_nbr_philo());
	if (philos == NUL)
		return (delete_forks());
	philos[0].forks[0] = get_forks() + (get_nbr_philo() - 1);
	i = 0;
	while (i < get_nbr_philo())
	{
		usleep(100);
		if (i != 0)
			philos[i].forks[0] = get_forks() + (i - 1);
		philos[i] = (t_philosopher){.id = i + 1, .forks[0] = philos[i].forks[0],
			.forks[1] = get_forks() + i};
		if (pthread_create(&philos[i].thread, NUL, &philospher_routine,
				philos + i) != 0)
			return (delete_philos(philos, i + 1));
		i += 2;
		if (i % 2 == 0 && i >= get_nbr_philo())
			i = 1;
	}
	return (philos);
}

int	run_simulation(t_philosopher *philos)
{
	t_pthread	thread;

	if (pthread_create(&thread, NUL, &time_routine, (void *)philos) != 0)
		return (1);
	if (pthread_join(thread, NUL) != 0)
		return (2);
	return (0);
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
