/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:21:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/17 14:05:14 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_timestamp	get_time(void)
{
	struct s_timeval	timeval;

	gettimeofday(&timeval, NUL);
	return ((t_timestamp){.sec = timeval.tv_sec, .usec = timeval.tv_usec});
}

t_uint64	ms_since(t_timestamp timestamp)
{
	t_timestamp	current_time;
	t_timestamp	delta_time;

	current_time = get_time();
	delta_time.sec = current_time.sec - timestamp.sec;
	delta_time.usec = current_time.usec - timestamp.usec;
	return ((delta_time.sec * 1000) + (delta_time.usec / 1000));
}
