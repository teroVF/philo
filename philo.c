/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/02 16:34:47 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (ft_str)
	//free
	exit(EXIT_FAILURE);
}

t_philo	*philo_init(t_program *program, int n)
{
	t_philo *socrates;
	
	socrates = malloc(sizeof(t_philo) * 1);
	socrates->pos = n + 1;
	socrates->even = ((n + 1) % 2 == 0) ? 1 : 0;
	socrates->last_meal = 0;
	socrates->program = program;
	return (socrates);	
}

void	*simulation_init(t_program *program, char **argv, int argc)
{
	int		n;

	n = 0;
	program->nbr_philo = (int) ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	program->meals = -1;
	if (argc == 6)
		program->meals = ft_atoi(argv[5]);
	if (program->nbr_philo <= 0 || program->time_eat < 0 || program->time_die < 0
		|| program->time_sleep < 0)
			error_msg("too low");
	program->tid = malloc(sizeof(pthread_t) * program->nbr_philo);
	if (program->tid != NULL)
		error_msg("");
	program->philo = malloc(sizeof(t_philo) * program->nbr_philo);
	if (program->tid != NULL)
		error_msg("");
	program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	if (program->tid != NULL)
		error_msg("");
	
	// program->philo = malloc(sizeof(t_philo *) * program->nbr_philo);
	// program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	// while (n < program->nbr_philo)
	// {
	// 	pthread_mutex_init(program->mutex_fork, NULL);
	// 	program->mutex_fork++;
	// 	n++;
	// }
	// n = 0;
	// while (n < program->nbr_philo)
	// {
	// 	program->philo[n] = philo_init(program, n);
	// 	n++;
	// }
	// return (program);
}

void	simulation(t_philo **philo)
{
	int n;
	n = 0;
	while (n < philo[0]->program->nbr_philo)
	{
		if(philo[n]->even == 1)
			pthread_create(&(philo[n]->thread), NULL, como_peixe, NULL);
		else if(philo[n]->even == 0)
			pthread_create(&(philo[n]->thread), NULL, como_galinha, NULL);
		n++;
	}
	for (int i = 0; i < philo[0]->program->nbr_philo; i++)
    {
        pthread_join(philo[i]->thread, NULL);
    }
}
/* ./philo number_of_philo time_to_die time_to_eat time_to_sleep [number eats] */
int main(int argc, char *argv[])
{
	t_program 	program;
	
	if (argc != 5 && argc != 6)
		error_msg(FEW_ARG);
	validation(argv, argc);
	simulation_init(&program, argv, argc);
	simulation(program);
	//free a tudo
}
