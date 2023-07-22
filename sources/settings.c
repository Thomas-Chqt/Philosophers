/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:06:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:28:14 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_uint64	get_setting_intern(t_setting setting, t_uint64 set_val);

int	init_settings(int argc, char const *argv[])
{
	t_uint64	nbr_philo;
	t_uint64	die_time;
	t_uint64	eat_time;
	t_uint64	sleep_time;
	t_uint64	must_eat;

	if (argc < 5 || argc > 6)
		return (-1);
	if (atoi_fill(argv[1], &nbr_philo) != 0)
		return (-1);
	if (atoi_fill(argv[2], &die_time) != 0)
		return (-1);
	if (atoi_fill(argv[3], &eat_time) != 0)
		return (-1);
	if (atoi_fill(argv[4], &sleep_time) != 0)
		return (-1);
	must_eat = 0;
	if (argc == 6 && atoi_fill(argv[5], &must_eat) != 0)
		return (-1);
	get_setting_intern(e_nbr_philo, nbr_philo);
	get_setting_intern(e_die_time, die_time);
	get_setting_intern(e_eat_time, eat_time);
	get_setting_intern(e_sleep_time, sleep_time);
	get_setting_intern(e_must_eat, must_eat);
	return (0);
}

t_uint64	get_setting(t_setting setting)
{
	return (get_setting_intern(setting, 0));
}

static t_uint64	get_setting_intern(t_setting setting, t_uint64 set_val)
{
	static t_uint64	settings[5] = {0};

	if (set_val != 0)
		settings[setting] = set_val;
	return (settings[setting]);
}
