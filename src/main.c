/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/09 02:43:04 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (ft_strcmp(error_msg, FEW_ARG) == 0)
	{
		ft_putstr_fd("Usage: ./philo number_of_philo", STDERR_FILENO);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep [number eats]\n", STDERR_FILENO);
	}
	//free
	exit(EXIT_FAILURE);
}

int 	check_meals(t_philo *philo)
{
	int i;

	i = 0;
	if (philo->program->meals == -1)
	{	
		printf("entrou\n");
		return (0);
	}
	// printf("numbr_meals: philo n:%d, meals %d\n", philo->pos, philo->numb_meals);
	while (i < philo->program->nbr_philo)
	{
		if (philo->program->philo[i]->numb_meals < philo->program->meals)
			return (0);
		i++;
	}
	return (1);
}

void stop_threads(t_philo **philo)
{
	int i;

	i = 0;
	while (i < philo[0]->program->nbr_philo)
	{
		pthread_detach(*philo[i]->tid);
		i++;
	}
}

void wait_and_check(t_philo **philo)
{
	while (1)
	{
		// if(check_death(philo) == 1)
		// 	break ;
		if (check_meals(*philo) == 1)
			break ;
	}
}


static void	simulation(t_philo **philo)
{
	int n;
	n = 0;
	while (n < philo[0]->program->nbr_philo)
	{
		printf("philo %d\n", philo[n]->sit);
		pthread_create(philo[n]->tid, NULL, &routine, philo[n]);
		ft_usleep(1000);
		n++;
	}
	// for (int i = 0; i < philo[0]->program->nbr_philo; i++)
    // {
    //     pthread_join(*philo[i]->tid, NULL);
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
	ft_putendl_fd("the simulation is running", STDOUT_FILENO);
	simulation_init(&program, av, ac);
	philo = program.philo;
	simulation(philo);
	//free a tudo
}
