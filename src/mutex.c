/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:12 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/14 01:32:14 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_mutex(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->program->nbr_philo)
	{
		pthread_mutex_destroy(&philo[0]->program->mutex_fork[i]);
		free(&philo[0]->program->mutex_fork[i]);
	}
	pthread_mutex_destroy(philo[0]->program->dead);
}

void mutex_init(t_program *program)
{
	int n;

	n = 0;
	while (n < program->nbr_philo)
	{
		pthread_mutex_init(&program->mutex_fork[n], NULL);
		n++;
	}
	program->dead = malloc(sizeof(pthread_mutex_t));
	program->write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(program->write, NULL);
	pthread_mutex_init(program->dead, NULL);
}