/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:50:35 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/22 19:11:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*create_forks(void)
{
	t_fork		*forks = NUL;
	t_uint64	i;

	forks = malloc(sizeof(t_fork) * get_gdata().nbr_philo);
	if (forks == NUL)
		return (NUL);
	i = 0;
	while (i < get_gdata().nbr_philo)
	{
		if (pthread_mutex_init(forks + i, NUL) != 0)
			return (delete_forks(forks, i + 1));
		i++;
	}
	return (forks);
}

void	*delete_forks(t_fork *forks, t_uint64 count)
{
	t_uint64	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
	free(forks);
	return (NUL);
}
