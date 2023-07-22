/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/21 17:24:29 by tchoquet         ###   ########.fr       */
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
		return (printf("Arguments Error\n"));
	if (init_time() != 0)
		return (printf("Unkown Error\n"));
	philosophers = create_philos();
	if (philosophers == NUL)
		return (printf("Unkown Error\n"));
	if (run_simulation(philosophers) != 0)
		return (printf("Unkown Error\n"));
	delete_philos(philosophers, get_setting(e_nbr_philo));
	return (0);
}
