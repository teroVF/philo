/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:35 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/28 00:10:06 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long long	utime(struct timeval t)
{
	return (t.tv_sec * 1000000 + t.tv_usec);
}

int	set_time(struct timeval *t)
{
	if (gettimeofday(t, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (1);
	}
	return (0);
}

time_t	deltatime(struct timeval t0, struct timeval t1)
{
	return ((utime(t1) - utime(t0)) / 1000);
}
