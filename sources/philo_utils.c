/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:04:24 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 16:20:45 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_fork	*create_forks(void);

t_fork	*get_forks(void)
{
	static t_fork	*forks = NUL;

	if (forks == NUL)
		forks = create_forks();
	return (forks);
}

void	*delete_forks(void)
{
	t_uint64	i;

	i = 0;
	while (i < get_nbr_philo())
	{
		pthread_mutex_destroy(get_forks() + i);
		i++;
	}
	free(get_forks());
	return (NUL);
}

static t_fork	*create_forks(void)
{
	t_fork		*forks;
	t_uint64	i;

	forks = malloc(sizeof(t_fork) * get_nbr_philo());
	if (forks == NUL)
		return (NUL);
	i = 0;
	while (i < get_nbr_philo())
	{
		if (pthread_mutex_init(forks + i, NUL) != 0)
		{
			if (i > 0)
			{
				i--;
				while (i < 0)
					pthread_mutex_destroy(forks + (i--));
				pthread_mutex_destroy(forks);
			}
			free(forks);
			return (NUL);
		}
		i++;
	}
	return (forks);
}
