/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:42:22 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/16 16:30:15 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "external_functions.h"

typedef	unsigned long	t_uint64;

typedef struct s_fork
{
	t_pthread_mutex	mutex;

}	t_fork;

typedef struct s_philosopher
{
	t_pthread	thread;
	t_fork		*fork1;
	t_fork		*fork2;
	t_uint64	last_eat_time;

}	t_philosopher;

int		check_args(int argc, char const *argv[]);
t_fork	create_fork(void);
void	create_philosopher(t_philosopher *philosopher, t_fork *fork1, t_fork *fork2);

long	atoi_long(const char *str);

#endif // PHILOSOPHERS_H