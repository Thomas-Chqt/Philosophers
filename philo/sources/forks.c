/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:50:35 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/22 22:57:13 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*create_forks(void)
{
	t_fork		*forks;
	t_uint64	i;
	t_uint64	y;

	forks = malloc(sizeof(t_fork) * get_gdata().nbr_philo);
	if (forks == NUL)
		return (NUL);
	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (pthread_mutex_init(forks + i, NUL) != 0)
		{
			y = 0;
			while (y < (i + 1))
			{
				pthread_mutex_destroy(forks + y);
				y++;
			}
			free(forks);
			return (NUL);
		}
		i++;
	}
	return (forks);
}

int	delete_forks(t_fork *forks, t_uint64 count)
{
	t_uint64	i;
	int			ret_val;

	ret_val = 0;
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(forks + i) != 0)
			ret_val = 1;
		i++;
	}
	free(forks);
	return (ret_val);
}
