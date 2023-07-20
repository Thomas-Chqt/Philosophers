/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_intern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:16:32 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 14:25:01 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_uint64	get_nbr_philo_intern(t_uint64 set_val)
{
	static t_uint64	val = 0;

	if (set_val != 0)
		val = set_val;
	return (val);
}

t_uint64	get_die_time_intern(t_uint64 set_val)
{
	static t_uint64	val = 0;

	if (set_val != 0)
		val = set_val;
	return (val);
}

t_uint64	get_eat_time_intern(t_uint64 set_val)
{
	static t_uint64	val = 0;

	if (set_val != 0)
		val = set_val;
	return (val);
}

t_uint64	get_sleep_time_intern(t_uint64 set_val)
{
	static t_uint64	val = 0;

	if (set_val != 0)
		val = set_val;
	return (val);
}

t_uint64	get_must_eat_intern(t_uint64 set_val)
{
	static t_uint64	val = 0;

	if (set_val != 0)
		val = set_val;
	return (val);
}
