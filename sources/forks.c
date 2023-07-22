/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:50:35 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:26:06 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_fork	*get_forks_intern(int create);

int	init_forks(void)
{
	if (get_forks_intern(1) == NUL)
		return (1);
	return (0);
}

t_fork	*get_forks(void)
{
	return (get_forks_intern(0));
}

void	*delete_forks(void)
{
	t_uint64	i;

	i = 0;
	while (i < get_setting(e_nbr_philo))
	{
		pthread_mutex_destroy(get_forks() + i);
		i++;
	}
	free(get_forks());
	return (NUL);
}

static t_fork	*get_forks_intern(int create)
{
	static t_fork	*forks = NUL;
	t_uint64		i;

	if (create == 0)
		return (forks);
	forks = malloc(sizeof(t_fork) * get_setting(e_nbr_philo));
	if (forks == NUL)
		return (NUL);
	i = -1;
	while (++i < get_setting(e_nbr_philo))
	{
		if (pthread_mutex_init(forks + i, NUL) != 0)
		{
			if (i-- > 0)
			{
				while (i > 0)
					pthread_mutex_destroy(forks + (i--));
				pthread_mutex_destroy(forks);
			}
			free(forks);
			return (NUL);
		}
	}
	return (forks);
}
