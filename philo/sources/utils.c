/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:21:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/19 21:24:48 by tchoquet         ###   ########.fr       */
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
	long		d_sec;
	long		d_usec;

	current_time = get_time();
	d_sec = current_time.sec - timestamp.sec;
	d_usec = current_time.usec - timestamp.usec;
	return ((d_sec * 1000) + (d_usec / 1000));
}

int	atoi_fill(char const *str, t_uint64 *nbr)
{
	unsigned int	i;

	*nbr = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((*nbr > ULONG_MAX / 10)
			|| (*nbr == ULONG_MAX / 10
				&& (t_uint64)(str[i] - '0') > ULONG_MAX % 10))
		{
			return (-1);
		}
		*nbr = (*nbr * 10) + (str[i] - '0');
		i++;
	}
	return (0);
}
