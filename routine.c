/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/01 02:22:02 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo, __ino64_t up)
{
    /* pegar nos dois garfos
    e depois eh que come! */

    pick_forks();
    //mutex ao garfos
    /* ft_usleep(eating time) */
    
    printf("%llu: the philo n %d is eating...\n", time, n_philo);
    if (meals == 1)
        /* aumenta meals */
    /* desbloquear mutex */
    
}

void    routine()
{
    void eating();
    void sleeping();
    void thinking();
}