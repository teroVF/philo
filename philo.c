/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/06 19:24:49 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
	exit(EXIT_FAILURE);
}

void	simulation_init(t_program *program, char **argv, int argc)
{
	int		n;

	n = 0;
	program = malloc(sizeof(t_program) * 1);
	program->nbr_philo = (int) ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->meals = argv[5];
	program->philo = malloc(sizeof(t_philo) * program->nbr_philo);
	program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	while (n < program->nbr_philo)
	{
		pthread_mutex_init(program->mutex_fork, NULL);
		program->mutex_fork++;
		n++;
	}
	philo_init(program);	
}

t_philo	*philo_init(t_program *program)
{
	int		n;
	t_philo *tmp;
	
	n = 0;
	while(n <= program->nbr_philo)
	{
		program->philo[n]->pos = n + 1;
		program->philo[n]->even = ((n + 1) % 2 == 0) ? 1 : 0;
		program->philo[n]->last_meal = 0;
		program->philo[n]->program = program;
		n++;
	}	
}

static int if_is_a_number(char *str)
{
	int		i;

	i = 0;

	if (!str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

void	validation(char **argv, int argc)
{
	int		i;
	
	i = 0;
	while (i < argc)
	{
		if(!if_is_a_number(argv[i]));
			error_msg(NOT_NBR);
		i++;
	}
}

/* ./philo number_of_philo time_to_die time_to_eat time_to_sleep [number eats] */
int main(int argc, char *argv[])
{
	t_program 	*program;
	
	if (argc != 5 && argc != 6)
		error_msg(FEW_ARG);
	validation(argv, argc);
	// simulation_init(program, argv, argc);
	// simulation(program);
	//free a tudo
}
