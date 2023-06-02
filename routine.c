/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/02 05:45:44 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    pick_forks()
{
    pthread_mutex_lock();
    //variavel
    printf("%llu: the philo pick the fork\n", time, philo->pos);
}

void eating(t_philo *philo, __ino64_t up)
{
    /* pegar nos dois garfos
    e depois eh que come! */
    pick_forks();
    pick_forks();
    pthread_mutex_unlock();
    pthread_mutex_unlock();
    printf("%llu: the philo n %d is eating...\n", time, philo->pos);
    ft_usleep(eating time);
    if (simulation->meals == 1)
        philo->numb_meals--;
    /* desbloquear mutex */
}

void    sleeping()
{
    ft_usleep();
    printf("%llu: the philo n %d is sleeping...\n", time, philo->pos);
}

void    routine()
{
    void eating();
    void sleeping();
    printf("%llu: the philo n %d is thinking...\n", time, philo->pos);
}