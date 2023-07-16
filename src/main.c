/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/16 14:06:49 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void data(t_program *program)
{
	printf("n_philos: %d\n", program->nbr_philo);
	printf("time_die: %lu\n", program->time_die);
	printf("time_eat: %lu\n", program->time_eat);
	printf("time_sleep: %lu\n", program->time_sleep);
	printf("meals: %d\n", program->meals);
}

static void	simulation(t_philo **philo)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (i < philo[0]->program->nbr_philo)
	{
		if (pthread_create(philo[i]->tid, NULL, routine, philo[i]))
			error_msg(CREATE_THREAD_ERROR);
		i+=2;
		if (i >= philo[0]->program->nbr_philo - 1 && flag == 0)
		{
			i = 1;
			flag = 1;
		}
	}
	i = 0;
	while (i < philo[0]->program->nbr_philo)
	{
		if (pthread_join(*philo[i]->tid, NULL))
			error_msg(JOIN_THREAD_ERROR);
		i++;
	}
}

int main(int ac, char *av[])
{
	t_program 	program;
	t_philo 	**philo;
	
	if (ac < 5)
		error_msg(FEW_ARG);
	if (ac > 6)
		error_msg(MANY_ARG);	
	validation(av, ac);
	simulation_init(&program, av, ac);
	data(&program);
	philo = program.philo;
	printf("similation will start\n");
	simulation(philo);
	free_everything(&program);
}
