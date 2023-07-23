/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:41:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 01:38:43 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#ifdef MEMCHECK

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
	int				return_code;
	t_fork			*forks;
	t_philosopher	*philosophers;

	return_code = 0;
	if (init_global_data(argc, argv) != 0)
		return (printf("Arguments Error\n"));
	if (init_time() != 0)
		return_code = printf("Unkown Error\n");
	else
	{
		forks = create_forks();
		if (forks == NUL)
			return_code = printf("Unkown Error\n");
		else
		{
			philosophers = create_philos(forks);
			if (philosophers == NUL)
				return_code = printf("Unkown Error\n");
			else if (run_philos(philosophers) != 0)
				return_code = printf("Unkown Error\n");
		}
	}
	if (delete_philos(philosophers) != 0)
		return_code = printf("Unkown Error\n");
	delete_forks(forks, get_gdata().nbr_philo);
	clean_gdata();
	return (return_code);
}
