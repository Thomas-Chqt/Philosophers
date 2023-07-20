/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:42:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 17:30:08 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "external_functions.h"

typedef unsigned long			t_uint64;

typedef struct s_timestamp		t_timestamp;
typedef struct s_philosopher	t_philosopher;

typedef t_pthread_mutex			t_fork;

struct s_timestamp
{
	t_uint64	sec;
	t_uint64	usec;
};

struct s_philosopher
{
	t_pthread	thread;
	t_uint64	id;
	t_fork		*forks[2];
	t_time		last_eat;
	t_uint64	eat_count;
};

int				init_time(void);
t_time			get_time(void);
t_time			time_since(t_time prev_time);
t_uint64		get_time_ms(void);

t_uint64		get_nbr_philo(void);
t_uint64		get_die_time(void);
t_uint64		get_eat_time(void);
t_uint64		get_sleep_time(void);
t_uint64		get_must_eat(void);

int				atoi_fill(char const *str, t_uint64 *nbr);

t_fork			*get_forks(void);
void			*delete_forks(void);

int				init_settings(int argc, char const *argv[]);
t_philosopher	*create_philos(void);
int				run_simulation(t_philosopher *philos);
void			*delete_philos(t_philosopher *philos, t_uint64 count);

void			*philospher_routine(void *data);
void			*time_routine(void *data);

#endif // PHILOSOPHERS_H