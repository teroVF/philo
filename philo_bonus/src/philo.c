/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/23 04:03:22 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void destroy_sem(t_program *program)
{
	sem_close(program->forks);
	sem_close(program->write);
	sem_close(program->dead);
	sem_close(program->stop);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("dead");
	sem_unlink("stop");
}

void free_program(t_program *program)
{
	int i;
	int n;

	i = -1;
	n = program->nbr_philo;

	destroy_sem(program);
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
		error_msg(MALLOC_ERROR);
	philo->sit = n + 1;
	philo->even = EVEN(philo->sit);
	philo->is_full = false;
	philo->dead = false;
	philo->eating = false;
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
	if (semaph_init(program) == 0)
		return (0);
	return (1);
}
