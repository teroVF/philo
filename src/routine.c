/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/04 16:10:01 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    eating(t_philo *philo)
{
    philo->last_meal = check_time(philo->program->start);
    if (philo->program->meals != -1)
        philo->numb_meals++;
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is eating...\n", check_time(philo->program->start) , philo->pos);
    pthread_mutex_unlock(&philo->program->write);
    ft_usleep(philo->program->time_eat * 1000);
}

void    sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is sleeping...\n", check_time(philo->program->start) , philo->pos);
    pthread_mutex_unlock(&philo->program->write);
    ft_usleep(philo->program->time_sleep * 1000);
}

void    pick_fork(t_philo *philo, int pos)
{
    pthread_mutex_lock(&philo->program->mutex_fork[pos -1]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->pos);
    pthread_mutex_unlock(&philo->program->write);
    if (pos == philo->program->nbr_philo -1)
        pthread_mutex_lock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_lock(&philo->program->mutex_fork[pos]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->pos);
    pthread_mutex_unlock(&philo->program->write);
}

void    left_fork(t_philo *philo, int pos)
{
    pthread_mutex_unlock(&philo->program->mutex_fork[pos -1]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d left fork left...\n", check_time(philo->program->start) , philo->pos);
    pthread_mutex_unlock(&philo->program->write);
    if (pos == philo->program->nbr_philo -1)
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_unlock(&philo->program->mutex_fork[pos]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d left fork right...\n", check_time(philo->program->start) , philo->pos);
    pthread_mutex_unlock(&philo->program->write);
}

void    *routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *) pointer;
    while (1)
    {
        pick_fork(philo, philo->pos);
        eating(philo);
        left_fork(philo, philo->pos);
        sleeping(philo);
        pthread_mutex_lock(&philo->program->write);
        printf("%lu, the philo n %d is thinking...\n", check_time(philo->program->start) , philo->pos);
        pthread_mutex_unlock(&philo->program->write);
    }
    return (NULL);
}