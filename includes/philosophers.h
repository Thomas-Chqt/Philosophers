/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:42:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/19 16:08:25 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "external_functions.h"

typedef unsigned long	t_uint64;

typedef struct s_timestamp
{
	t_uint64	sec;
	t_uint64	usec;

}	t_timestamp;

typedef struct settings
{
	t_uint64	nbr_philo;
	t_uint64	time_die;
	t_uint64	time_eat;
	t_uint64	time_sleep;
	t_uint64	nbr_eat;
	t_timestamp	start_time;

}	t_settings;

typedef struct s_philo
{
	t_pthread		thread;
	t_settings		settings;
	t_uint64		id;
	t_pthread_mutex	*fork1;
	t_pthread_mutex	*fork2;
	t_timestamp		last_eat;
	t_uint64		eat_count;

}	t_philo;

int			setup(int argc, char const *argv[], t_settings *settings);
void		create_philo(t_philo *philo, t_settings settings,
				t_pthread_mutex *fork1, t_pthread_mutex *fork2);
void		start_simulation(t_pthread *time_thread, t_philo *philos,
				t_settings settings);

t_timestamp	get_time(void);
t_uint64	ms_since(t_timestamp timestamp);
int			atoi_fill(char const *str, t_uint64 *nbr);
#endif // PHILOSOPHERS_H