/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:27:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/16 16:32:04 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	atoi_long(const char *str)
{
	t_uint64		nbr;
	unsigned int	i;

	nbr = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((nbr > ULONG_MAX / 10) || (nbr == ULONG_MAX / 10 && (t_uint64)(str[i] - '0') > ULONG_MAX % 10))
			return (0);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr);
}
