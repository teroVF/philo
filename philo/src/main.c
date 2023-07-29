/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/29 15:59:40 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	data(t_program *program)
{
	printf("n_philos: %d\n", program->nbr_philo);
	printf("time_die: %lu ms\n", program->time_die);
	printf("time_eat: %lu ms\n", program->time_eat);
	printf("time_sleep: %lu ms\n", program->time_sleep);
	if (program->meals != -1)
		printf("meals: %d\n", program->meals);
}

static int	join_threads(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->program->nbr_philo)
	{
		if (pthread_join(philo[i]->tid, NULL))
			return (error_msg(JOIN_THREAD_ERROR));
	}
	return (0);
}

static int	simulation(t_philo **philo)
{
	int		i;

	i = -1;
	set_time(&philo[0]->program->start);
	while (++i < philo[0]->program->nbr_philo)
	{
		philo[i]->last_meal = philo[i]->program->start;
		if (pthread_create(&philo[i]->tid, NULL, routine, *(philo + i)))
			return (error_msg(CREATE_THREAD_ERROR));
	}
	if (pthread_create(&philo[0]->program->check_time, NULL,
			monitor, philo[0]->program))
		return (error_msg(CREATE_THREAD_ERROR));
	if (philo[0]->program->nbr_philo == 1)
	{
		if (pthread_join(philo[0]->program->check_time, NULL))
			return (error_msg(JOIN_THREAD_ERROR));
	}
	else
		pthread_detach(philo[0]->program->check_time);
	i = -1;
	if (join_threads(philo) == 1)
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_program	program;
	t_philo		**philo;

	if (ac < 5)
		return (error_msg(FEW_ARG));
	else if (ac > 6)
		return (error_msg(MANY_ARG));
	if (!validate_args(av, ac))
		return (EXIT_FAILURE);
	memset(&program, 0, sizeof(t_program));
	if (!simulation_init(&program, av, ac))
	{
		free_program(&program);
		return (EXIT_FAILURE);
	}
	philo = program.philo;
	data(&program);
	if (simulation(philo) == 1)
	{
		free_program(philo[0]->program);
		return (EXIT_FAILURE);
	}
	free_program(philo[0]->program);
	return (EXIT_SUCCESS);
}
