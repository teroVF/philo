/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/13 11:59:53 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    eating(t_philo *philo)
{
    philo->last_meal = check_time(philo->program->start);
    if (philo->program->meals != -1)
        philo->numb_meals++;
    // pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is eating...\n", check_time(philo->program->start) , philo->sit);
    // pthread_mutex_unlock(&philo->program->write);
    ft_usleep(philo->program->time_eat * 1000);
}

void    sleeping(t_philo *philo)
{
    // pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d is sleeping...\n", check_time(philo->program->start) , philo->sit);
    // pthread_mutex_unlock(&philo->program->write);
    ft_usleep(philo->program->time_sleep * 1000);
}

void    pick_fork(t_philo *philo, int sit)
{
    printf("%d\n", philo->sit);
    printf("nbr_philo: %d\n", philo->program->nbr_philo);
    if (philo->sit == philo->program->nbr_philo && philo->program->nbr_philo % 2)
    {
        pthread_mutex_lock(&philo->program->mutex_fork[0]);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_lock(&philo->program->mutex_fork[philo->sit - 1]);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
    }
    else
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        if (sit == philo->program->nbr_philo)
            pthread_mutex_lock(&philo->program->mutex_fork[0]);
        else
            pthread_mutex_lock(&philo->program->mutex_fork[sit]);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
    }
}

void    left_fork(t_philo *philo, int sit)
{
        if (philo->sit == philo->program->nbr_philo && philo->program->nbr_philo % 2)
    {
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(&philo->program->mutex_fork[philo->sit - 1]);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        return ;
    }
    pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
    printf("%lu, the philo n %d left fork left...\n", check_time(philo->program->start) , philo->sit);
    if (sit == philo->program->nbr_philo)
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_unlock(&philo->program->mutex_fork[sit]);
    // pthread_mutex_lock(&philo->program->write);
    printf("%lu, the philo n %d left fork right...\n", check_time(philo->program->start) , philo->sit);
    // pthread_mutex_unlock(&philo->program->write);
}
int is_dead(t_philo *philo)
{
    if (philo[0].program->someone_dead == 1)
        return (1);
    return (0);
}


void    *routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *) pointer;
    while (1)
    {
        if (is_dead(philo) == 1)
            break ;
        if (is_dead(philo) == 0)
            pick_fork(philo, philo->sit);
        if (is_dead(philo) == 0)
            eating(philo);
        if (is_dead(philo) == 0)
            left_fork(philo, philo->sit);
        if (philo->program->meals != -1 && philo->numb_meals == philo->program->meals)
            break ;
        if (is_dead(philo) == 0)
            sleeping(philo);
        // pthread_mutex_lock(&philo->program->write);
        if (is_dead(philo) == 0)
            printf("%lu, the philo n %d is thinking...\n", check_time(philo->program->start) , philo->sit);
        // pthread_mutex_unlock(&philo->program->write);
    }
    return (NULL);
}