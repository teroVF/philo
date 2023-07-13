/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/13 12:05:41 by anvieira         ###   ########.fr       */
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
		pthread_mutex_init(&program->mutex_fork[n], NULL);
		n++;
	}
	program->dead = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(program->dead, NULL);
}

t_philo	*philo_init(t_program *program, int n)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	philo->tid = malloc(sizeof(pthread_t));
	philo->sit = n + 1;
	philo->even = ((n + 1) % 2 == 0) ? 1 : 0;
	philo->last_meal = 0;
	philo->is_full = 0;
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
	program->someone_dead = 0;
	if (argc == 6)
		program->meals = (int) ft_atoi(argv[5]);
	program->philo = malloc(sizeof(t_philo *) * program->nbr_philo + 1);
	while (n < program->nbr_philo)
	{
		program->philo[n] = philo_init(program, n);
		n++;
	}
	program->philo[n] = NULL;
	mutex_init(program);
}
