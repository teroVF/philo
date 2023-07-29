/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/29 15:56:25 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	eating(t_philo *philo)
{
	int		sit;

	sit = philo->sit;
	print_msg(philo, EATING);
	pthread_mutex_lock(&philo->program->m_stop);
	set_time(&philo->last_meal);
	if (philo->program->meals != -1 && philo->is_full == FALSE)
		philo->numb_meals++;
	pthread_mutex_unlock(&philo->program->m_stop);
	usleep(philo->program->time_eat * 1000);
	pthread_mutex_unlock(&philo->program->mutex_fork
	[sit % philo->program->nbr_philo]);
	pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
}

static void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	usleep(philo->program->time_sleep * 1000);
}

static void	pick_forks(t_philo *philo, int sit)
{
	if (!(philo->sit % 2 == 0))
	{
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
		print_msg(philo, FORK);
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
		print_msg(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
		print_msg(philo, FORK);
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
		print_msg(philo, FORK);
	}
}

static void	one_philo(t_philo *philo)
{
	print_msg(philo, FORK);
	while (1){
		pthread_mutex_lock(&philo->program->m_stop);
		if (philo->program->stop == 1)
		{
			pthread_mutex_unlock(&philo->program->m_stop);
			return ;
		}
		pthread_mutex_unlock(&philo->program->m_stop);
	}
}

void	*routine(void *pointer)
{
	t_philo		*philo;

	philo = (t_philo *) pointer;
	if (philo->program->nbr_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->even)
		usleep((philo->program->time_eat / 2) * 1000);
	while (1)
	{
		pick_forks(philo, philo->sit);
		eating(philo);
		sleeping(philo);
		print_msg(philo, THINKING);
		pthread_mutex_lock(&philo->program->m_stop);
		if (philo->program->stop == 1)
		{
			pthread_mutex_unlock(&philo->program->m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->program->m_stop);
	}
	return (NULL);
}
