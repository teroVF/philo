/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/27 00:51:54 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void free_mutex(t_program *program)
{
	int i;
	int n;

	i = -1;
	n = program->nbr_philo;
	pthread_mutex_destroy(&program->m_stop);
	pthread_mutex_destroy(&program->write);
	while (++i < n)
	{
		if (&program->mutex_fork[i] != NULL && program->mutex_fork != NULL)
			pthread_mutex_destroy(&program->mutex_fork[i]);
	}
	free(program->mutex_fork);
}

void free_program(t_program *program)
{
	int i;
	int n;

	i = -1;
	n = program->nbr_philo;
	free_mutex(program);
	i = -1;
	while (++i < n)
		free(program->philo[i]);
	free(program->philo);
}

t_philo	*philo_init(t_program *program, int n)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
	{
		error_msg(MALLOC_ERROR);
		return (NULL);
	}
	philo->sit = n + 1;
	philo->even = EVEN(philo->sit);
	philo->is_full = false;
	philo->dead = false;
	philo->program = program;
	if (program->meals != -1)
		philo->numb_meals = 0;
	else
		philo->numb_meals = -1;
	return (philo);	
}

int	simulation_init(t_program *program, char **argv, int argc)
{
	int		n;

	n = -1;
	program->nbr_philo = (int)ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	program->meals = -1;
	if (argc == 6)
		program->meals = (int) ft_atoi(argv[5]);
	program->philo = malloc(sizeof(t_philo *) * program->nbr_philo);
	if (program->philo == NULL)
		return (error_msg(MALLOC_ERROR));
	while (++n < program->nbr_philo)
		program->philo[n] = philo_init(program, n);
	if (mutex_init(program) == 0)
		return (0);
	return (1);
}
