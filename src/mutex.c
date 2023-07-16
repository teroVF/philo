/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:12 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/16 14:15:18 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void mutex_init(t_program *program)
{
	int n;

	n = 0;
	
	program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	while (n < program->nbr_philo)
	{
		if (pthread_mutex_init(&program->mutex_fork[n], NULL) != 0)
			error_msg(MUTEX_ERROR_FORK);
		n++;
	}
	program->dead = malloc(sizeof(pthread_mutex_t));
	program->write = malloc(sizeof(pthread_mutex_t));
	if (program->dead == NULL || program->write == NULL)
		error_msg(MALLOC_ERROR);
	if (pthread_mutex_init(program->dead, NULL) != 0)
		error_msg(MUTEX_ERROR_DEAD);
	if (pthread_mutex_init(program->write, NULL) != 0)
		error_msg(MUTEX_ERROR_WRITE);
}