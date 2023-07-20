/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 17:16:11 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifdef MEMCHECK

# include <Libft.h>
# include <unistd.h>
# include <stdlib.h>

__attribute__((destructor))
static void	destructor(void)
{
	char	*pid;
	char	*cmd;

	pid = ft_itoa(getpid());
	cmd = ft_strjoin("leaks -q ", pid);
	ft_printf("\n \n");
	system((const char *)cmd);
	free(pid);
	free(cmd);
}

#endif // MEMCHECK

int	main(int argc, char const *argv[])
{
	t_philosopher	*philosophers;

	if (init_settings(argc, argv) != 0)
	{
		printf("Arguments Error\n");
		return (1);
	}
	philosophers = create_philos();
	if (philosophers == NUL || run_simulation(philosophers) != 0)
		printf("Unkown Error\n");
	if (philosophers != NUL)
	{
		delete_philos(philosophers, get_nbr_philo());
		return (3);
	}
	else
		return (2);
	delete_philos(philosophers, get_nbr_philo());
	return (0);
}
