/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/29 03:47:50 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	pick_forks(t_philo *philo)
{
	sem_wait(philo->program->forks);
	sem_wait(philo->program->forks);
	print_msg(philo, FORK);
}

void	eating(t_philo *philo)
{
	print_msg(philo, EATING);
	set_time(&philo->last_meal);
	if (philo->program->meals != -1)
		philo->numb_meals++;
	usleep(philo->program->time_eat * 1000);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	usleep(philo->program->time_sleep * 1000);
}

int		one_philo(t_philo *philo)
{
	print_msg(philo, FORK);
	while (1)
		;
}
void *monitor(void *arg)
{
	t_philo *philo;
	int flag_all_eat;
	struct timeval	time;
	int flag;

	
	philo = (t_philo *)arg;
	flag = 0;
	flag_all_eat = 0;
	while (1)
	{
		sem_wait(philo->program->dead);
		set_time(&time);
		if (deltatime(philo->last_meal, time) > philo->program->time_die)
		{
			print_msg(philo, DEAD);
			printf("adeus\n");
			exit(1);
		}
		sem_post(philo->program->dead);	
		sem_wait(philo->program->dead);
		if (philo->program->meals != -1 && philo->numb_meals == philo->program->meals 
			&& flag == 0)
		{
			sem_post(philo->program->eat);
			flag = 1;
		}
		sem_post(philo->program->dead);	
		
	}
	return	(NULL);
}

int	routine(t_philo *philo)
{
	if (pthread_create(&philo->check_events, NULL, monitor, philo) != 0)
		return (error_msg(CREATE_THREAD_ERROR));
	if (pthread_detach(philo->check_events) != 0)
		return (error_msg(JOIN_THREAD_ERROR));
	if (philo->program->nbr_philo == 1)
	{
		one_philo(philo);
		return (1);
	}
	while (1)
	{
		pick_forks(philo);
		eating(philo);
		sleeping(philo);
		print_msg(philo, THINKING);
	}
}
