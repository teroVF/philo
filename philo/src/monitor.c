/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 02:53:30 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/30 17:09:58 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*if_philo_died(t_philo *philo)
{
	print_msg(philo, DEAD);
	return (NULL);
}

static int	if_everybody_is_full(t_program *program, int i)
{
	static int	flag;

	if (program->meals != -1 && program->philo[i]->numb_meals == program->meals 
		&& program->philo[i]->is_full == FALSE)
	{
		flag += 1;
		program->philo[i]->is_full = TRUE;
	}
	if (flag == program->nbr_philo)
	{
		program->stop = 1;
		pthread_mutex_unlock(&program->m_stop);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_program		*program;
	struct timeval	time;
	int				i;

	program = (t_program *) arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&program->m_stop);
		set_time(&time);
		if (deltatime(program->philo[i]->last_meal, time) > program->time_die)
		{
			pthread_mutex_unlock(&program->m_stop);
			if_philo_died(program->philo[i]);
			return (NULL);
		}
		if (if_everybody_is_full(program, i))
			return (NULL);
		pthread_mutex_unlock(&program->m_stop);
		i++;
		if (i == program->nbr_philo)
			i = 0;
	}
	return (NULL);
}
