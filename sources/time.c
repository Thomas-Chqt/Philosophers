/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:34:17 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 17:33:03 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_time	internal_get_time(t_time set_srt_time);

int	init_time(void)
{
	struct s_timeval	timeval;

	if (gettimeofday(&timeval, NUL) != 0)
		return (1);
	(void)internal_get_time((t_timestamp){
		.sec = (t_uint64)timeval.tv_sec,
		.usec = (t_uint64)timeval.tv_usec
	});
	return (0);
}

t_timestamp	get_time(void)
{
	return (internal_get_time((t_timestamp){
			.sec = 0,
			.usec = 0
		}));
}

static t_time	internal_get_time(t_time set_srt_time)
{
	static t_time		start_time;
	struct s_timeval	timeval;
	long				d_sec;
	long				d_usec;
	t_uint64			d_ms;

	if (set_srt_time != 0)
		start_time = set_srt_time;
	if (gettimeofday(&timeval, NUL) != 0)
		return (0);
	d_sec = timeval.tv_sec - start_time.sec;
	d_usec = timeval.tv_usec - start_time.usec;
	return ((t_timestamp){
		.sec = (t_uint64)timeval.tv_sec - start_time.sec,
		.usec = (t_uint64)timeval.tv_usec - start_time.usec
	});
}

t_uint64	ms_since(t_timestamp prev_time)
{
	t_timestamp	current_time;
	long		d_sec;
	long		d_usec;

	current_time = get_time();
	if ((prev_time.sec > current_time.sec)
		|| ((prev_time.sec == current_time.sec)
			&& (prev_time.usec > current_time.usec)))
	d_sec = current_time.sec - prev_time.sec;
	d_usec = current_time.usec - prev_time.usec;
	return ((t_uint64)((d_sec * 1000) + (d_usec / 1000)));
}

t_uint64	get_time_ms(void)
{
	t_timestamp	time;

	time = get_time();
	return ((t_uint64)((time.sec * 1000) + (time.usec / 1000)));
}