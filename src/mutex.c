/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:12 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/27 01:02:59 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	mutex_write_init(t_program *program)
{
	if (pthread_mutex_init(&program->write, NULL) != 0)
		return (error_msg(MUTEX_ERROR_WRITE));
	printf("mutex write: %p\n", &program->write);
	return (0);
}

static int	mutex_stop_init(t_program *program)
{
	if (pthread_mutex_init(&program->m_stop, NULL) != 0)
		return (error_msg(MUTEX_ERROR_STOP));
	printf("mutex stop: %p\n", &program->m_stop);
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
		printf("mutex fork[%d]: %p\n", n, &program->mutex_fork[n]);
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
