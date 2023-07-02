/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:35 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/09 14:14:51 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__ino64_t    milliseconds(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    ft_usleep(__int64_t mi_s)
{
    __int64_t   start;
    start = milliseconds();
    while ((milliseconds() - start) * 1000 < mi_s)
		continue ;
}

__int64_t   check_time(__int64_t start)
{
    __int64_t real_time;
    
	real_time = (milliseconds()) - start;
    return (real_time);
}

int 	main(void)
{
	__int64_t start = milliseconds();
	ft_usleep(3000000);
	__int64_t how_much = check_time(start);
	printf("%ld\n", how_much);
	return 0;
}