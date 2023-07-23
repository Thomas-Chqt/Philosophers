/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:06:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 13:59:17 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_global_data	get_gdata_intern(t_global_data set_val, t_bool set);

int	init_global_data(int argc, char const *argv[])
{
	t_global_data	global_data;

	global_data = (t_global_data){0};
	if (argc < 5 || argc > 6)
		return (1);
	if (atoi_fill(argv[1], &global_data.nbr_philo) != 0
		|| global_data.nbr_philo == 0
		|| atoi_fill(argv[2], (t_uint64 *)&global_data.die_time) != 0
		|| atoi_fill(argv[3], (t_uint64 *)&global_data.eat_time) != 0
		|| atoi_fill(argv[4], (t_uint64 *)&global_data.sleep_time) != 0
		|| (argc == 6 && atoi_fill(argv[5], &global_data.must_eat) != 0))
		return (1);
	global_data.need_eat_left = global_data.nbr_philo;
	global_data.global_mutex = malloc(sizeof(t_pthread_mutex));
	if (global_data.global_mutex == NUL)
		return (1);
	if (pthread_mutex_init(global_data.global_mutex, NUL) != 0)
	{	
		free(global_data.global_mutex);
		return (1);
	}
	get_gdata_intern(global_data, true);
	return (0);
}

t_global_data	get_gdata(void)
{
	return (get_gdata_intern((t_global_data){0}, false));
}

void	set_need_eat_left(t_uint64 val)
{
	t_global_data	current_data;

	current_data = get_gdata();
	current_data.need_eat_left = val;
	if (current_data.need_eat_left == 0)
		current_data.is_finished = true;
	get_gdata_intern(current_data, true);
}

void	clean_gdata(void)
{
	pthread_mutex_destroy(get_gdata().global_mutex);
	free(get_gdata().global_mutex);
}

static t_global_data	get_gdata_intern(t_global_data set_val, t_bool set)
{
	static t_global_data	global_data = {0};

	if (set == true)
		global_data = set_val;
	return (global_data);
}
