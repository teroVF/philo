/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/11 02:37:14 by anvieira         ###   ########.fr       */
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

void	free_mutex(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->program->nbr_philo)
	{
		pthread_mutex_destroy(&philo[0]->program->mutex_fork[i]);
		free(&philo[0]->program->mutex_fork[i]);
	}
	pthread_mutex_destroy(&philo[0]->program->write);
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
int check_death(t_philo **philo, int i)
{
	__uint64_t limite;
	__uint64_t time;

	limite = philo[i]->last_meal + philo[i]->program->time_die;
	time = check_time(philo[0]->program->start);
	if (time > limite + 10)
	{
		pthread_mutex_lock(&philo[i]->program->write);
		printf("%lu %d died\n", time - 10, philo[i]->sit);
		pthread_mutex_unlock(&philo[i]->program->write);
		return (1);
	}
	return (0);
}

int check_is_full(t_philo **philo, int i)
{
	static int count = 0;
	
	if (philo[i]->numb_meals == philo[0]->program->meals 
		&& philo[i]->is_full == 0)
	{
		pthread_mutex_lock(&philo[i]->program->write);
		printf("%lu %d is full\n", check_time(philo[0]->program->start),
			philo[i]->sit);
		pthread_mutex_unlock(&philo[i]->program->write);
		count++;
		philo[i]->is_full = 1;
		if (count == philo[0]->program->nbr_philo)
			return (1);
	}
	return (0);
}

void wait_and_check(t_philo **philo)
{
	int i;
	
	i = 0;
	while (1)
	{
		if (check_is_full(philo, i) == 1)
			break ;
		if(check_death(philo, i) == 1)
			break ;
		i++;
		if (i == philo[0]->program->nbr_philo)
			i = 0;
	}
}


static void	simulation(t_philo **philo)
{
	int n;
	int flag;
	
	flag = 0;
	n = 0;
	printf("philo %d\n", philo[0]->program->nbr_philo);
	if (!(philo[0]->program->nbr_philo % 2))
	{
		while (n < philo[0]->program->nbr_philo)
		{
			printf("philo %d\n", philo[n]->sit);
			pthread_create(philo[n]->tid, NULL, &routine, philo[n]);
			if (!(philo[0]->program->nbr_philo % 2))
				n +=2;
			if (n == philo[0]->program->nbr_philo && flag == 0)
			{
				n = 1;
				flag = 1;
			}
		}
	}
	else
	{
		while (n < philo[0]->program->nbr_philo - 1)
		{
			printf("philo %d\n", philo[n]->sit);
			pthread_create(philo[n]->tid, NULL, &routine, philo[n]);
			if ((philo[0]->program->nbr_philo % 2))
				n +=2;
			if (n == philo[0]->program->nbr_philo - 1 && flag == 0)
			{
				n = 1;
				flag = 1;
			}
		}
		printf("philo %d\n", philo[philo[0]->program->nbr_philo -1]->sit);
		pthread_create(philo[philo[0]->program->nbr_philo -1]->tid, NULL, &routine, philo[philo[0]->program->nbr_philo -1]);
		
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
	// free_mutex(philo);
}
