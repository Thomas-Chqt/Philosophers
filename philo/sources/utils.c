/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:21:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/20 17:07:47 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	atoi_fill(char const *str, t_uint64 *nbr)
{
	unsigned int	i;

	*nbr = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((*nbr > ULONG_MAX / 10)
			|| (*nbr == ULONG_MAX / 10
				&& (t_uint64)(str[i] - '0') > ULONG_MAX % 10))
		{
			return (-1);
		}
		*nbr = (*nbr * 10) + (str[i] - '0');
		i++;
	}
	return (0);
}
