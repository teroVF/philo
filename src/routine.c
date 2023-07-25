/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:23:05 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/25 00:37:55 by anvieira         ###   ########.fr       */
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

void*	is_dead(void *arg)
{
	time_t	limite;
	t_program	*program;
	int i = 0;
	
	while (1)
	{
		program = (t_program *) arg;
		pthread_mutex_lock(program->dead);
		limite = program->philo[i]->last_meal + program->time_die;
		if (program->someone_dead)
		{
			if (program->philo[i]->eating == true)
				unlock_fork_when_dead(program->philo[i]);
			pthread_mutex_unlock(program->dead);
			exit (0);
		}
		pthread_mutex_unlock(program->dead);
		pthread_mutex_lock(program->dead);
		if (check_time(program->start) > limite)
		{
			if (program->philo[i]->eating == true)
				unlock_fork_when_dead(program->philo[i]);
			if_philo_died(program->philo[i]);
			pthread_mutex_unlock(program->dead);
			exit(0);
		}
		pthread_mutex_unlock(program->dead);
		i++;
		if (i == program->nbr_philo)
			i = 0;
	}
	return (NULL);
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
	if (philo->even)
	{
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
	}
	else
	{
		pthread_mutex_lock(&philo->program->mutex_fork
		[sit % philo->program->nbr_philo]);
		pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
	}
	philo->eating = true;
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
	while(1)
	{
		if (philo->sit % 2 == 0)
			ft_usleep(10 *1000);
		pick_forks(philo, philo->sit);
		eating(philo);
		sleeping(philo);
		print_msg(philo, THINKING);
	}
	return (NULL);
}
