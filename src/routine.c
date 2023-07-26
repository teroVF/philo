/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/26 04:29:54 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void *if_philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->program->m_stop);
	philo->program->stop = 1;
	pthread_mutex_unlock(philo->program->m_stop);
	philo->dead = true;
	print_msg(philo, DEAD);
	return (NULL);
}

int stop(t_philo *philo)
{
	pthread_mutex_lock(philo->program->m_stop);
	if (philo->program->stop)
	{
		pthread_mutex_unlock(philo->program->m_stop);
		return (0);
	}
	pthread_mutex_unlock(philo->program->m_stop);
	return (1);
}

void*	is_dead(void *arg)
{
	time_t	limite;
	t_program	*program;
	int i;
	int flag_all_eat;
	
	flag_all_eat = 0;
	i = 0;
	program = (t_program *) arg;
	while (1)
	{
		limite = program->philo[i]->last_meal + program->time_die;
		if (check_time(program->start) > limite)
			return (if_philo_died(program->philo[i]));
		if (program->meals != -1 && program->philo[i]->numb_meals == program->meals)
				flag_all_eat++;
		if (flag_all_eat == program->nbr_philo)
		{
			pthread_mutex_lock(program->m_stop);
			program->stop = 1;
			pthread_mutex_unlock(program->m_stop);
			return (NULL);
		}
		i++;
		if (i == program->nbr_philo)
		{
			flag_all_eat = 0;
			i = 0;
		}
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	int		sit;

	sit = philo->sit;
	philo->last_meal = check_time(philo->program->start);
	print_msg(philo, EATING);
	ft_usleep(philo->program->time_eat * 1000);
	pthread_mutex_unlock(&philo->program->mutex_fork
	[sit % philo->program->nbr_philo]);
	pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
	philo->eating = false;
	if (philo->program->meals != -1)
		philo->numb_meals++;
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	ft_usleep(philo->program->time_sleep * 1000);
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
	philo->eating = true;
}



void	*routine(void *pointer)
{
	t_philo		*philo;
	
	philo = (t_philo *) pointer;
	while(stop(philo))
	{	
		if (!(philo->sit % 2 == 0))
			ft_usleep(1000);
		pick_forks(philo, philo->sit);
		eating(philo);
		sleeping(philo);
		print_msg(philo, THINKING);
	}
	return (NULL);
}
