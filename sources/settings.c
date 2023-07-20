/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:06:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 14:22:08 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_uint64	get_nbr_philo_intern(t_uint64 set_val);
t_uint64	get_die_time_intern(t_uint64 set_val);
t_uint64	get_eat_time_intern(t_uint64 set_val);
t_uint64	get_sleep_time_intern(t_uint64 set_val);
t_uint64	get_must_eat_intern(t_uint64 set_val);

t_uint64	get_nbr_philo(void)
{
	return (get_nbr_philo_intern(0));
}

t_uint64	get_die_time(void)
{
	return (get_die_time_intern(0));
}

t_uint64	get_eat_time(void)
{
	return (get_eat_time_intern(0));
}

t_uint64	get_sleep_time(void)
{
	return (get_sleep_time_intern(0));
}

t_uint64	get_must_eat(void)
{
	return (get_must_eat_intern(0));
}
