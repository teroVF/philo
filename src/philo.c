/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/16 14:01:55 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void free_everything(t_program *program)
{
	int i;
	int n;

	i = -1;
	n = program->nbr_philo;
	while (++i < n)
		pthread_mutex_destroy(&program->mutex_fork[i]);
	pthread_mutex_destroy(program->dead);
	pthread_mutex_destroy(program->write);
	free(program->mutex_fork);
	free(program->dead);
	free(program->write);
	i = -1;
	while (++i < n)
		free(program->philo[i]->tid);
	i = -1;
	while (++i <= n)
		free(program->philo[i]);
	free(program->philo);
}

t_philo	*philo_init(t_program *program, int n)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		error_msg(MALLOC_ERROR);
	philo->tid = malloc(sizeof(pthread_t));
	if (philo->tid == NULL)
		error_msg(MALLOC_ERROR);
	philo->sit = n + 1;
	philo->even = EVEN(philo->sit);
	philo->last_meal = check_time(program->start);
	philo->is_full = false;
	philo->dead = false;
	philo->program = program;
	if (program->meals != -1)
		philo->numb_meals = 0;
	else
		philo->numb_meals = -1;
	return (philo);	
}

void	simulation_init(t_program *program, char **argv, int argc)
{
	int		n;

	n = 0;
	program->nbr_philo = (int)ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	program->meals = -1;
	program->start = check_time(0);
	program->someone_dead = false;
	if (argc == 6)
		program->meals = (int) ft_atoi(argv[5]);
	program->philo = malloc(sizeof(t_philo *) * program->nbr_philo + 1);
	if (program->philo == NULL)
		error_msg(MALLOC_ERROR);
	while (n < program->nbr_philo)
	{
		program->philo[n] = philo_init(program, n);
		n++;
	}
	program->philo[n] = NULL;
	mutex_init(program);
}
