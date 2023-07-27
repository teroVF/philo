/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/27 17:50:03 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void *if_philo_died(t_philo *philo)
{
	print_msg(philo, DEAD);
	return (NULL);
}

void*	is_dead(void *arg)
{
	t_program	*program;
	int i;
	// int flag_all_eat;
	// flag_all_eat = 0;
	struct timeval time;
	i = 0;
	program = (t_program *) arg;
	while (1)
	{
		pthread_mutex_lock(&program->m_stop);
		set_time(&time);
		// printf("time: %lld\n", utime(time));
		// printf("time die: %ld\n", program->time_die);
		// printf("time eat: %lld\n", utime(program->philo[i]->last_meal));
		// printf("diff: %lld\n", deltatime(program->philo[i]->last_meal, time));
		if (deltatime(program->philo[i]->last_meal, time) > program->time_die)
		{
			pthread_mutex_unlock(&program->m_stop);
			return (if_philo_died(program->philo[i]));
		}
		// if (program->meals != -1 && program->philo[i]->numb_meals == program->meals)
		// 		flag_all_eat++;
		// if (flag_all_eat == program->nbr_philo)
		// {
		// 	program->stop = 1;
		// 	pthread_mutex_unlock(&program->m_stop);
		// 	return (NULL);
		// }
		pthread_mutex_unlock(&program->m_stop);
		i++;
		if (i == program->nbr_philo)
		{
			// flag_all_eat = 0;
			i = 0;
		}
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	int		sit;

	sit = philo->sit;
	print_msg(philo, EATING);
	pthread_mutex_lock(&philo->program->m_stop);
	set_time(&philo->last_meal);
	if (philo->program->meals != -1)
		philo->numb_meals++;
	pthread_mutex_unlock(&philo->program->m_stop);
	usleep(philo->program->time_eat * 1000);
	pthread_mutex_unlock(&philo->program->mutex_fork
	[sit % philo->program->nbr_philo]);
	pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	usleep(philo->program->time_sleep * 1000);
}

void	pick_forks(t_philo *philo, int sit)
{
	if (!(philo->sit % 2 == 0))
	{
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
	}
	print_msg(philo, FORK);
}

void	*routine(void *pointer)
{
	t_philo		*philo;
	
	philo = (t_philo *) pointer;
	print_msg(philo, THINKING);
	if (!(philo->even))
		usleep((philo->program->time_eat / 2) * 1000);
	while(1)
	{	
		pick_forks(philo, philo->sit);
		eating(philo);
		sleeping(philo);
		pthread_mutex_lock(&philo->program->m_stop);
		print_msg(philo, THINKING);
		if (philo->program->stop == 1)
		{
			pthread_mutex_unlock(&philo->program->m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->program->m_stop);
	}
	return (NULL);
}
