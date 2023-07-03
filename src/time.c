/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:35 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/03 17:09:10 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static __int64_t    milliseconds(void)
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
