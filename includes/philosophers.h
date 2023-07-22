/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:42:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:26:50 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "external_functions.h"

typedef unsigned long			t_uint64;
typedef unsigned long			t_time;

typedef struct s_timestamp		t_timestamp;
typedef struct s_philosopher	t_philosopher;
typedef enum e_setting			t_setting;

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

enum e_setting
{
	e_nbr_philo = 0,
	e_die_time = 1,
	e_eat_time = 2,
	e_sleep_time = 3,
	e_must_eat = 4
};

int				init_time(void);
t_time			get_time(void);
t_time			time_since(t_time prev_time);

int				init_settings(int argc, char const *argv[]);
t_uint64		get_setting(t_setting setting);

int				init_forks(void);
t_fork			*get_forks(void);
void			*delete_forks(void);

t_philosopher	*create_philos(void);
void			*delete_philos(t_philosopher *philos, t_uint64 count);

int				run_simulation(t_philosopher *philos);

int				take_fork(t_philosopher *philo, t_fork *fork);
int				eat(t_philosopher *philo);
int				drop_fork(t_fork *fork);
int				philo_sleep(t_philosopher *philo);
int				think(t_philosopher *philo);

int				atoi_fill(char const *str, t_uint64 *nbr);

#endif // PHILOSOPHERS_H