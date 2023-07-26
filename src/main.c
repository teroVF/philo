/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/26 02:14:08 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void data(t_program *program)
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
	int i;
	
	i = -1;
	philo[0]->program->start = milliseconds();
	while (++i < philo[0]->program->nbr_philo)
	{
		pthread_create(&philo[i]->tid, NULL, routine, *(philo +i));
		pthread_detach(philo[i]->tid);
		ft_usleep(50);
	}
	pthread_create(&philo[0]->program->check_time, NULL, is_dead, philo[0]->program);
	pthread_join(philo[0]->program->check_time, NULL);
}

int main(int ac, char *av[])
{
	t_program 	program;
	t_philo 	**philo;
	
	if (ac < 5)
	{
		error_msg(FEW_ARG);
		return (EXIT_FAILURE);
	}
	if (ac > 6)
	{
		error_msg(MANY_ARG);
		return (EXIT_FAILURE);
	}	
	if (!validate_args(av, ac))
		return (EXIT_FAILURE);
	memset(&program, 0, sizeof(t_program));
	if (!simulation_init(&program, av, ac))
	{
		free_program(&program);
		return (EXIT_FAILURE);
	}
	philo = program.philo;
	printf("similation will start\n");
	data(&program);
	simulation(philo);
	free_program(&program);
	return (EXIT_SUCCESS);
}
