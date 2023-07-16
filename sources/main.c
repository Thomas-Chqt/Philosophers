/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/16 16:30:08 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char const *argv[])
{		
	t_uint64		fophi_count;
	t_fork			*forks;
	t_philosopher	*philosophers;
	t_uint64		i;

	if (check_args(argc, argv) != 0)
		return (printf("Arguments Error"));
	fophi_count = atoi_long(argv[1]);
	forks = malloc(sizeof(t_fork) * fophi_count);
	if (forks == NULL)
		return (printf("Malloc Error"));
	philosophers = malloc(sizeof(t_philosopher) * fophi_count);
	if (philosophers == NULL)
	{
		free(forks);
		return (printf("Malloc Error"));
	}
	i = 0;
	while (i < fophi_count)
		forks[i++] = create_fork();
	create_philosopher(philosophers, forks + (fophi_count - 1), forks);
	i = 0;
	while (i < fophi_count)
	{
		create_philosopher(philosophers + i, forks + (i - 1), forks + i);
		i++;
	}

	return (0);
}

