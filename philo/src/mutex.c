/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:12 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/28 00:54:14 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	mutex_write_init(t_program *program)
{
	if (pthread_mutex_init(&program->write, NULL) != 0)
		return (error_msg(MUTEX_ERROR_WRITE));
	return (0);
}

static int	mutex_stop_init(t_program *program)
{
	if (pthread_mutex_init(&program->m_stop, NULL) != 0)
		return (error_msg(MUTEX_ERROR_STOP));
	return (0);
}

static int	mutex_fork_init(t_program *program)
{
	int	n;

	n = 0;
	program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	while (n < program->nbr_philo)
	{
		if (pthread_mutex_init(&program->mutex_fork[n], NULL) != 0)
			return (error_msg(MUTEX_ERROR_FORK));
		n++;
	}
	return (0);
}

int	mutex_init(t_program *program)
{
	if (mutex_fork_init(program) != 0)
		return (0);
	if (mutex_write_init(program) != 0)
		return (0);
	if (mutex_stop_init(program) != 0)
		return (0);
	return (1);
}
