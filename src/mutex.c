/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:12 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/17 02:04:43 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	int	mutex_dead_init(t_program *program)
{
	program->dead = malloc(sizeof(pthread_mutex_t));
	if (program->dead == NULL)
		return (error_msg(MALLOC_ERROR));
	if (pthread_mutex_init(program->dead, NULL) != 0)
		return (error_msg(MUTEX_ERROR_DEAD));
	return (1);
}

static int  mutex_write_init(t_program *program)
{
	program->write = malloc(sizeof(pthread_mutex_t));
	if (program->write == NULL)
		return (error_msg(MALLOC_ERROR));
	if (pthread_mutex_init(program->write, NULL) != 0)
		return (error_msg(MUTEX_ERROR_DEAD));
	return (1);
}

static int mutex_fork_init(t_program *program)
{
		int n;

	n = 0;
	program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	while (n < program->nbr_philo)
	{
		if (pthread_mutex_init(&program->mutex_fork[n], NULL) != 0)
			return (error_msg(MUTEX_ERROR_FORK));
		n++;
	}
	return (1);
}
int mutex_init(t_program *program)
{
	if (mutex_fork_init(program) == 0)
		return (0);
	if (mutex_dead_init(program) == 0)
		return (0);
	if (mutex_write_init(program) == 0)
		return (0);
	return (1);
}
