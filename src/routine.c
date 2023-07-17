/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/17 04:14:43 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void unlock_fork_when_dead(t_philo *philo)
{
	pthread_mutex_unlock(&philo->program->mutex_fork[philo->sit - 1]);
	pthread_mutex_unlock(&philo->program->mutex_fork
	[philo->sit % philo->program->nbr_philo]);
	philo->eating = false;
}

void if_philo_died(t_philo *philo)
{
	if (!philo->program->someone_dead)
	{
		philo->program->someone_dead = 1;
		philo->dead = true;
		print_msg(philo, DEAD);
	}
}

int	is_dead(t_philo *philo)
{
	time_t	limite;

	pthread_mutex_lock(philo->program->dead);
	limite = philo->last_meal + philo->program->time_die + 10;
	if (philo->program->someone_dead)
	{
		if (philo->eating == true)
			unlock_fork_when_dead(philo);
		pthread_mutex_unlock(philo->program->dead);
		return (1);
	}
	if (check_time(philo->program->start) > limite)
	{
		if (philo->eating == true)
			unlock_fork_when_dead(philo);
		if_philo_died(philo);
		pthread_mutex_unlock(philo->program->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->program->dead);
	return (0);
}

void	eating(t_philo *philo)
{
	int		sit;

	sit = philo->sit;
	print_msg(philo, EATING);
	philo->last_meal = check_time(philo->program->start);
	if (philo->program->meals != -1)
		philo->numb_meals++;
	ft_usleep(philo->program->time_eat * 1000);
	print_msg(philo, LEAVE_FORK);
	pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
	pthread_mutex_unlock(&philo->program->mutex_fork
	[sit % philo->program->nbr_philo]);
	philo->eating = false;
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	ft_usleep(philo->program->time_sleep * 1000);
}

int	pick_forks(t_philo *philo, int sit)
{
	if (philo->even && !is_dead(philo))
	{
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
	}
	else if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
	}
	philo->eating = true;
	if (is_dead(philo))
		return (0);
	print_msg(philo, FORK);
	return (1);
}

void	*one_philo(t_philo *philo)
{
	print_msg(philo, I_AM_ALONE);
	ft_usleep(philo->program->time_die * 1000);
	print_msg(philo, DEAD);
	return (NULL);
}

void	*routine(void *pointer)
{
	t_philo		*philo;
	
	philo = (t_philo *) pointer;
	if (philo->program->nbr_philo == 1)
		return (one_philo(philo));
	if (!is_dead(philo))
	{
		if (!pick_forks(philo, philo->sit))
			return (NULL);
	}
	if (!is_dead(philo))
		eating(philo);
	if (philo->program->meals != -1
		&& philo->numb_meals == philo->program->meals)
	{
		print_msg(philo, FULL);
		return (NULL);
	}
	if (!is_dead(philo))
		sleeping(philo);
	if (!is_dead(philo))
		print_msg(philo, THINKING);
	if (!is_dead(philo))
		routine(philo);
	return (NULL);
}
