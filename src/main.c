/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/14 02:24:37 by anvieira         ###   ########.fr       */
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
	int n;
	int flag;
	
	flag = 0;
	n = 0;
	if (!(philo[0]->program->nbr_philo % 2))
	{
		while (n < philo[0]->program->nbr_philo)
		{
			printf("philo %d\n", philo[n]->sit);
			pthread_create(philo[n]->tid, NULL, &routine, philo[n]);
			n += 2;
			if (n == philo[0]->program->nbr_philo && flag == 0)
			{
				n = 1;
				flag = 1;
				ft_usleep(2000);
			}
		}
	}
	// else
	// {
	// 	while (n < philo[0]->program->nbr_philo - 1)
	// 	{
	// 		printf("philo %d\n", philo[n]->sit);
	// 		pthread_create(philo[n]->tid, NULL, &routine, philo[n]);
	// 		n += 2;
	// 		if (n == philo[0]->program->nbr_philo - 1 && flag == 0)
	// 		{
	// 			n = 1;
	// 			flag = 1;
	// 		}
	// 	}
	// 	printf("philo %d\n", philo[philo[0]->program->nbr_philo -1]->sit);
	// 	pthread_create(philo[philo[0]->program->nbr_philo -1]->tid, NULL, &routine, philo[philo[0]->program->nbr_philo -1]);
		
	// }
	wait_and_check(philo);
	stop_threads(philo);
}

int main(int ac, char *av[])
{
	t_program 	program;
	t_philo 	**philo;
	
	if (ac != 5 && ac != 6)
		error_msg(FEW_ARG);	
	validation(av, ac);
	data(&program);
	ft_putendl_fd("SIMULATION BEGINS:", STDOUT_FILENO);
	simulation_init(&program, av, ac);
	philo = program.philo;
	simulation(philo);
	// free_mutex(philo);
}
