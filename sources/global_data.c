/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:06:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/22 18:36:10 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_global_data	get_gdata_intern(t_global_data set_val, int set);

int	init_global_data(int argc, char const *argv[])
{
	t_global_data	global_data;

	global_data = (t_global_data){0};
	if (argc < 5 || argc > 6)
		return (-1);
	if (atoi_fill(argv[1], &global_data.nbr_philo) != 0
		|| global_data.nbr_philo == 0)
		return (-1);
	if (atoi_fill(argv[2], (t_uint64 *)&global_data.die_time) != 0)
		return (-1);
	if (atoi_fill(argv[3], (t_uint64 *)&global_data.eat_time) != 0)
		return (-1);
	if (atoi_fill(argv[4], (t_uint64 *)&global_data.sleep_time) != 0)
		return (-1);
	if (argc == 6 && atoi_fill(argv[5], &global_data.must_eat) != 0)
		return (-1);
	get_gdata_intern(global_data, 1);
	return (0);
}

t_global_data	get_gdata(void)
{
	return (get_gdata_intern((t_global_data){0}, 0));
}

static t_global_data	get_gdata_intern(t_global_data set_val, int set)
{
	static t_global_data	global_data = {0};

	if (set != 0)
		global_data = set_val;
	return (global_data);
}
