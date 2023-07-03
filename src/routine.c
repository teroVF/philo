/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/03 17:09:04 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    pick_forks(t_philo *philo)
{
    pthread_mutex_lock();
    printf("%llu: the philo pick the fork\n", time, philo->pos);
}

void eating(t_philo *philo)
{
    /* pegar nos dois garfos
    e depois eh que come! */
    pick_forks();
    pick_forks();
    printf("%llu: the philo n %d is eating...\n", time, philo->pos);
    ft_usleep(philo->program->time_eat);
    printf("%llu: the philo n %d drop the fork...\n", time, philo->pos);
    if (philo->program->meals == 1)
        philo->numb_meals--;
    pthread_mutex_unlock();
    printf("%llu: the philo n %d drop the fork...\n", time, philo->pos);
    pthread_mutex_unlock();
    if(philo->numb_meals == 0)
    {
        printf("the philo n %d finish his routine");
        exit(0);
    }
    /* desbloquear mutex */
}

void    sleeping(t_philo *philo)
{
    ft_usleep(philo->program->time_sleep);
    printf("%llu: the philo n %d is sleeping...\n", time, philo->pos);
}

void    *routine(t_philo *philo)
{
    void eating(philo);
    void sleeping(philo);
    printf("%llu: the philo n %d is thinking...\n", time, philo->pos);
    return NULL;
}