/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:34:17 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 20:26:18 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_time	internal_get_time(struct s_timeval set_srt_time);

int	init_time(void)
{
	struct s_timeval	timeval;

	if (gettimeofday(&timeval, NUL) != 0)
		return (1);
	(void)internal_get_time(timeval);
	return (0);
}

t_time	get_time(void)
{
	return (internal_get_time((struct s_timeval){.tv_sec = 0, .tv_usec = 0}));
}

t_time	time_since(t_time prev_time)
{
	return (get_time() - prev_time);
}

static t_time	internal_get_time(struct s_timeval set_srt_time)
{
	static struct s_timeval	start_time;
	struct s_timeval		current_time;
	long					d_sec;
	long					d_usec;

	if (set_srt_time.tv_sec != 0 || set_srt_time.tv_usec != 0)
		start_time = set_srt_time;
	if (gettimeofday(&current_time, NUL) != 0)
		return (0);
	d_sec = current_time.tv_sec - start_time.tv_sec;
	d_usec = current_time.tv_usec - start_time.tv_usec;
	return ((t_uint64)((d_sec * 1000) + (d_usec / 1000)));
}
