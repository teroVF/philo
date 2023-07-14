/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/14 01:10:20 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->program->write);
    philo->last_meal = check_time(philo->program->start);
    if (philo->program->meals != -1)
        philo->numb_meals++;
    printf("%lu, the philo n %d is eating...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(philo->program->write);
    ft_usleep(philo->program->time_eat * 1000);
}

void    sleeping(t_philo *philo)
{
    pthread_mutex_lock(philo->program->write);
    printf("%lu, the philo n %d is sleeping...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(philo->program->write);
    ft_usleep(philo->program->time_sleep * 1000);
}

void    pick_right_fork(t_philo *philo, int sit)
{
    if (sit != philo->program->nbr_philo)
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->time);
    }
    else
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->time);
    }
}
void    pick_left_fork(t_philo *philo, int sit)
{
    if (sit != philo->program->nbr_philo)
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->time);
    }
    else
    {
        pthread_mutex_lock(&philo->program->mutex_fork[0]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->time);
    }
}

void    left_fork(t_philo *philo, int sit)
{
        if (philo->sit == philo->program->nbr_philo)
    {
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
        pthread_mutex_lock(philo->program->write);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->write);
        pthread_mutex_unlock(&philo->program->mutex_fork[philo->sit - 1]);
        pthread_mutex_lock(philo->program->write);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->write);
        return ;
    }
    pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
    printf("%lu, the philo n %d left fork left...\n", check_time(philo->program->start) , philo->sit);
    if (sit == philo->program->nbr_philo)
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_unlock(&philo->program->mutex_fork[sit]);
    pthread_mutex_lock(philo->program->write);
    printf("%lu, the philo n %d left fork right...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(philo->program->write);
}
int is_dead(t_philo *philo)
{
    int a;
    a = 0;
    
    pthread_mutex_lock(philo->program->dead);
    if (philo[0].program->someone_dead == 1)
        a = 1;
    pthread_mutex_unlock(philo->program->dead);
    if (a == 1)
        return (1);
    else
        return (0);
}


void    *routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *) pointer;
    while (1)
    {
        pick_right_fork(philo, philo->sit);
        pick_left_fork(philo, philo->sit);
        eating(philo);
        left_fork(philo, philo->sit);
        sleeping(philo);
        pthread_mutex_lock(philo->program->write);
        printf("%lu, the philo n %d is thinking...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->write);
    }
    return (NULL);
}