/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:35 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/07 22:19:38 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

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
