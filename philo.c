/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/08 02:49:52 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
	exit(EXIT_FAILURE);
}

t_philo	*philo_init(t_program *program, int n)
{
	t_philo *socrates;
	pthread_t tpm;
	
	socrates = malloc(sizeof(t_philo) * 1);
	socrates->thread = tpm;
	socrates->pos = n + 1;
	socrates->even = ((n + 1) % 2 == 0) ? 1 : 0;
	socrates->last_meal = 0;
	socrates->program = program;
	return (socrates);	
}
t_program	*simulation_init(t_program *program, char **argv, int argc)
{
	int		n;

	n = 0;
	
	program = malloc(sizeof(t_program) * 1);
	if (program == NULL)
		error_msg("malloc ui");
	program->nbr_philo = (int) ft_atoi(argv[1]);
	printf("time: %d\n", program->nbr_philo);
	program->time_die = ft_atoi(argv[2]);
	printf("time: %lu\n", program->time_die);
	program->time_eat = ft_atoi(argv[3]);
	printf("time: %lu\n", program->time_eat);
	program->time_sleep = ft_atoi(argv[4]);
	printf("time: %lu\n", program->time_sleep);
	if (argc == 6)
		program->meals = ft_atoi(argv[5]);
	program->philo = malloc(sizeof(t_philo *) * program->nbr_philo);
	program->mutex_fork = malloc(sizeof(pthread_mutex_t) * program->nbr_philo);
	while (n < program->nbr_philo)
	{
		pthread_mutex_init(program->mutex_fork, NULL);
		program->mutex_fork++;
		n++;
	}
	n = 0;
	while (n < program->nbr_philo)
	{
		program->philo[n] = philo_init(program, n);
		n++;
	}
	return (program);
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
	
	i = 1;
	while (i < argc)
	{
		if(!if_is_a_number(argv[i]))
			error_msg(NOT_NBR);
		i++;
	}
	printf("perfeito\n");
}

/* ./philo number_of_philo time_to_die time_to_eat time_to_sleep [number eats] */
int main(int argc, char *argv[])
{
	t_program 	*program;
	
	if (argc != 5 && argc != 6)
		error_msg(FEW_ARG);
	validation(argv, argc);
	program = simulation_init(program, argv, argc);
	printf("%lu\n", program->time_die);
	printf("%lu\n", program->time_eat);
	printf("%lu\n", program->time_sleep);
	printf("o primeiro: %p\n", (void *) program->philo[0]->thread);
	printf("o primeiro: %d\n", program->philo[0]->even);
	printf("o segundo philo: %p\n", (void *) program->philo[1]->thread);
	printf("o segundo philo: %d\n", program->philo[1]->even);
	printf("o primeiro: %lu\n", program->philo[2]->thread);
	printf("o primeiro: %d\n", program->philo[2]->even);
	printf("o segundo philo: %lu\n", program->philo[3]->thread);
	printf("o segundo philo: %d\n", program->philo[3]->even);
	// simulation(program);
	//free a tudo
}
