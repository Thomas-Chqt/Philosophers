/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:55:00 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 16:48:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_FUNCTIONS_H
# define EXTERNAL_FUNCTIONS_H

# define ULONG_MAX 18446744073709551615UL
# define __PTHREAD_MUTEX_SIZE__ 56
# define NUL ((void *)0)

typedef unsigned long						t_size;
typedef long								t_ssize;
typedef unsigned int						t_useconds;
typedef long								t_time;
typedef int									t_suseconds;
typedef struct _opaque_pthread_t			*t_pthread;
typedef struct _opaque_pthread_attr_t		t_pthread_attr;
typedef struct s_opaque_pthread_mutex		t_pthread_mutex;
typedef struct _opaque_pthread_mutexattr_t	t_pthread_mutexattr;

struct s_timeval
{
	t_time		tv_sec;
	t_suseconds	tv_usec;
};

struct s_opaque_pthread_mutex {
	long	__sig;
	char	__opaque[__PTHREAD_MUTEX_SIZE__];
};

void	*memset(void *b, int c, t_size len);
int		printf(const char *format, ...);
void	*malloc(t_size size);
void	free(void *ptr);
t_ssize	write(int fildes, const void *buf, t_size nbyte);
int		usleep(t_useconds microseconds);
int		gettimeofday(struct s_timeval *tp, void *tzp);
int		pthread_create(t_pthread *thread, const t_pthread_attr *attr,
			void *(*start_routine)(void *), void *arg);
int		pthread_detach(t_pthread thread);
int		pthread_join(t_pthread thread, void **value_ptr);
int		pthread_mutex_init(t_pthread_mutex *mutex,
			const t_pthread_mutexattr *attr);
int		pthread_mutex_destroy(t_pthread_mutex *mutex);
int		pthread_mutex_lock(t_pthread_mutex *mutex);
int		pthread_mutex_unlock(t_pthread_mutex *mutex);

#endif // EXTERNAL_FUNCTIONS_H