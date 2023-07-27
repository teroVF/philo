/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/27 02:19:23 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	data(t_program *program)
{
	printf("n_philos: %d\n", program->nbr_philo);
	printf("time_die: %lu\n", program->time_die);
	printf("time_eat: %lu\n", program->time_eat);
	printf("time_sleep: %lu\n", program->time_sleep);
	if (program->meals != -1)
		printf("meals: %d\n", program->meals);
}

static void	simulation(t_philo **philo)
{
	int		i;

	i = -1;
	set_time(philo[0]->program->off_set_time);
	while (++i < philo[0]->program->nbr_philo)
	{
		pthread_create(&philo[i]->tid, NULL, routine, *(philo + i));
	}
	pthread_create(&philo[0]->program->check_time, NULL,
		is_dead, philo[0]->program);
	pthread_detach(philo[0]->program->check_time);
	i = -1;
	// while (++i < philo[0]->program->nbr_philo)
	// 	pthread_join(philo[i]->tid, NULL);
	while (1)
		;
	
	free_program(philo[0]->program);
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
	simulation(philo);
	return (EXIT_SUCCESS);
}
