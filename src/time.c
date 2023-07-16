/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:35 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/15 13:51:53 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static time_t    milliseconds(void)
{
    struct timeval time;
    
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    ft_usleep(time_t mi_s)
{
    time_t  start;
    start = milliseconds();
    while ((milliseconds() - start) * 1000 < mi_s)
		continue ;
}

time_t   check_time(time_t start)
{
    time_t real_time;
    
	real_time = (milliseconds()) - start;
    return (real_time);
}