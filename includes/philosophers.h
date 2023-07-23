/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:42:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 01:39:38 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "external_functions.h"

# ifdef MEMCHECK

char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
int				system(const char *command);
int				getpid(void);
int				ft_printf(const char *format, ...);

# endif // MEMCHECK

typedef unsigned long			t_uint64;
typedef unsigned long			t_time;

typedef t_pthread_mutex			t_fork;

typedef struct s_philosopher	t_philosopher;
typedef struct s_global_data	t_global_data;
typedef enum e_bool				t_bool;

enum e_bool { false = 0, true = 1 };

struct s_philosopher
{
	t_pthread	thread;
	t_bool		is_thread_created;
	t_uint64	id;
	t_fork		*forks[2];
	t_time		last_eat;
	t_uint64	eat_left;
};

struct s_global_data
{
	t_pthread_mutex	*global_mutex;
	t_uint64		nbr_philo;
	t_time			die_time;
	t_time			eat_time;
	t_time			sleep_time;
	t_uint64		must_eat;
	t_uint64		need_eat_left;
	t_bool			is_finished;
};

int				init_time(void);
t_time			get_time(void);
t_time			time_since(t_time prev_time);

int				init_global_data(int argc, char const *argv[]);
t_global_data	get_gdata(void);
void			need_eat_left_minus_one(void);
void			clean_gdata(void);

t_fork			*create_forks(void);
int				delete_forks(t_fork *forks, t_uint64 count);

t_philosopher	*create_philos(t_fork *forks);
int				run_philos(t_philosopher *philos);
int				delete_philos(t_philosopher *philos);

int				take_fork(t_philosopher *philo, t_fork *fork);
int				eat(t_philosopher *philo);
int				drop_fork(t_fork *fork);
int				philo_sleep(t_philosopher *philo);
int				think(t_philosopher *philo);

int				atoi_fill(char const *str, t_uint64 *nbr);

#endif // PHILOSOPHERS_H