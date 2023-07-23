/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 14:42:32 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifdef MEMCHECK

__attribute__((destructor))
static void	destructor(void)
{
	char	*pid;
	char	*cmd;

	print_report();
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
	int				return_code;
	t_fork			*forks;
	t_philosopher	*philosophers;

	return_code = 1;
	if (init_global_data(argc, argv) != 0)
		return (printf("Arguments Error\n"));
	if (init_time() == 0)
	{
		forks = create_forks();
		philosophers = create_philos(forks);
		if (philosophers != NUL)
		{
			if (run_philos(philosophers) == 0)
				return_code = 0;
			delete_philos(philosophers);
			delete_forks(forks, get_gdata().nbr_philo);
		}
	}
	clean_gdata();
	if (return_code != 0)
		printf("Unkown Error\n");
	return (return_code);
}
