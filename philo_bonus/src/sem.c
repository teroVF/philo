/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:29:12 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/23 04:01:45 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int sem_init_stop(t_program *program)
{
	sem_unlink("stop");
	program->stop = sem_open("stop", O_CREAT, 0644, 1);
	if (program->stop == SEM_FAILED)
		return (error_msg(SEM_ERROR_FORK));
	return (1);
}

static int sem_init_forks(t_program *program)
{
	sem_unlink("forks");
	program->forks = sem_open("forks", O_CREAT, 0644, program->nbr_philo);
	if (program->forks == SEM_FAILED)
		return (error_msg(SEM_ERROR_FORK));
	return (1);
}
static int sem_init_dead(t_program *program)
{
	sem_unlink("dead");
	program->dead = sem_open("dead", O_CREAT, 0644, 1);
	if (program->dead == SEM_FAILED)
		return (error_msg(SEM_ERROR_FORK));
	return (1);
}

static int sem_init_write(t_program *program)
{
	sem_unlink("write");
	program->write = sem_open("write", O_CREAT, 0644, 1);
	if (program->write == SEM_FAILED)
		return (error_msg(SEM_ERROR_FORK));
	return (1);
}

int semaph_init(t_program *program)
{
	if (sem_init_forks(program) == 0)
		return (0);
	if (sem_init_write(program) == 0)
		return (0);
	if (sem_init_dead(program) == 0)
		return (0);
	if (sem_init_stop(program) == 0)
		return (0);
	
	return (1);
}
