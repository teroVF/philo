/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/10 02:10:38 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    eating(t_philo *philo)
{
    philo->last_meal = check_time(philo->program->start);
    if (philo->program->meals != -1)
        philo->numb_meals++;
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is eating...\n", check_time(philo->program->start) , philo->sit);
    printf("the philo n %d already ate %d times\n",philo->sit, philo->numb_meals);
    pthread_mutex_unlock(&philo->program->write);
    ft_usleep(philo->program->time_eat * 1000);
}

void    sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is sleeping...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(&philo->program->write);
    ft_usleep(philo->program->time_sleep * 1000);
}

void    pick_fork(t_philo *philo, int sit)
{
    pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(&philo->program->write);
    if (sit == philo->program->nbr_philo)
        pthread_mutex_lock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_lock(&philo->program->mutex_fork[sit]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(&philo->program->write);
}

void    left_fork(t_philo *philo, int sit)
{
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d left fork left...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(&philo->program->write);
    pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
    if (sit == philo->program->nbr_philo)
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_unlock(&philo->program->mutex_fork[sit]);
    pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d left fork right...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(&philo->program->write);
}

void    *routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *) pointer;
    while (1)
    {
        if (philo->program->meals != -1 && philo->numb_meals == philo->program->meals)
            break ;
        if (philo->program->dead == 1)
            break ;
        pick_fork(philo, philo->sit);
        pthread_mutex_lock(&philo->program->eat);
        eating(philo);
        pthread_mutex_unlock(&philo->program->eat);
        left_fork(philo, philo->sit);
        sleeping(philo);
        pthread_mutex_lock(&philo->program->write);
        printf("%lu, the philo n %d is thinking...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(&philo->program->write);
    }
    return (NULL);
}