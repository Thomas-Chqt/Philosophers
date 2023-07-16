/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:42:14 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/16 16:30:29 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_loop(void *data);

int	check_args(int argc, char const *argv[])
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (atoi_long(argv[1]) == 0 || atoi_long(argv[2]) == 0)
		return (-1);
	if (atoi_long(argv[3]) == 0 || atoi_long(argv[4]) == 0)
		return (-1);
	if (argc == 6 && atoi_long(argv[5]) == 0)
		return (-1);	
	return (0);
}

t_fork	create_fork(void)
{
	t_pthread_mutex	mutex;

	pthread_mutex_init(&mutex, NULL);
	return ((t_fork){mutex});
}

void	create_philosopher(t_philosopher *philosopher, t_fork *fork1, t_fork *fork2)
{
	philosopher->fork1 = fork1;
	philosopher->fork2 = fork2;
	philosopher->last_eat_time = 0;
	pthread_create(&philosopher->thread, NULL, &philosopher_loop, philosopher);
}

void	*philosopher_loop(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	while (1)
	{
		pthread_mutex_lock(&philosopher->fork1->mutex);
		printf("Philo took fork");
		pthread_mutex_lock(&philosopher->fork1->mutex);
		printf("Philo took fork");
	}
	
}