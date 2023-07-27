/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/27 03:49:08 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	pick_forks(t_philo *philo)
{
	sem_wait(philo->program->forks);
	sem_wait(philo->program->forks);
	print_msg(philo, FORK);
	philo->eating = true;
	return (1);
}

void	eating(t_philo *philo)
{
	print_msg(philo, EATING);
	philo->last_meal = check_time(0);
	if (philo->program->meals != -1)
		philo->numb_meals++;
	ft_usleep(philo->program->time_eat * 1000);
	print_msg(philo, LEAVE_FORK);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
	philo->eating = false;
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	ft_usleep(philo->program->time_sleep * 1000);
}


int		one_philo(t_philo *philo)
{
	print_msg(philo, TOOk_ONE_FORK);
	ft_usleep(philo->program->time_die * 1000);
	print_msg(philo, DEAD);
	return (1);
}
void *check_events(void *arg)
{
	t_philo *philo;
	int flag_all_eat;
	flag_all_eat = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->program->dead);
		if (check_time(philo->last_meal) > philo->program->time_die)
		{
			print_msg(philo, DEAD);
			exit(1);
		}
		sem_post(philo->program->dead);
		sem_wait(philo->program->dead);
		if (philo->program->meals != -1 && philo->numb_meals == philo->program->meals)
		{
			flag_all_eat++;
			exit(0);
		}
		sem_post(philo->program->dead);
	}
	return	(NULL);
}



int	routine(t_philo *philo)
{
	if (pthread_create(&philo->check_events, NULL, check_events, philo) != 0)
		return (error_msg(CREATE_THREAD_ERROR));
	if (pthread_detach(philo->check_events) != 0)
		return (error_msg(JOIN_THREAD_ERROR));
	if (philo->program->nbr_philo == 1)
	{
		one_philo(philo);
		return (1);
	}
	sem_wait(philo->program->write);
	printf("endereco do programa: %p\n", philo->program);
	sem_post(philo->program->write);
	philo->last_meal = check_time(0);
	while (1)
	{
		pick_forks(philo);
		eating(philo);
		sleeping(philo);
		print_msg(philo, THINKING);
	}
}
