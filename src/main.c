/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/14 01:38:51 by anvieira         ###   ########.fr       */
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

void	free_mutex(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->program->nbr_philo)
	{
		pthread_mutex_destroy(&philo[0]->program->mutex_fork[i]);
		free(&philo[0]->program->mutex_fork[i]);
	}
	pthread_mutex_destroy(philo[0]->program->dead);
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
		// pthread_mutex_lock(&philo[i]->program->write);
		printf("%lu %d died\n", time - 10, philo[i]->sit);
		philo[i]->program->someone_dead = 1;
		// pthread_mutex_unlock(&philo[i]->program->write);
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
		// pthread_mutex_lock(&philo[i]->program->write);
		printf("%lu %d is full\n", check_time(philo[0]->program->start),
			philo[i]->sit);
		// pthread_mutex_unlock(&philo[i]->program->write);
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
		if  (philo[0]->program->meals != -1 && check_is_full(philo, i) == 1)
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
	free_mutex(philo);
}
