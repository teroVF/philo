/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/28 03:49:46 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void data(t_program *program)
{
	printf("n_philos: %d\n", program->nbr_philo);
	printf("time_die: %lu\n", program->time_die);
	printf("time_eat: %lu\n", program->time_eat);
	printf("time_sleep: %lu\n", program->time_sleep);
	if (program->meals != -1)
		printf("meals: %d\n", program->meals);
}
void exit_program(t_philo **philo)
{
	int i;
	i = 0;
	int status;
	printf("endereco do programa: %p\n", philo[0]->program);
	while (i < philo[0]->program->nbr_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			while (i < philo[0]->program->nbr_philo)
			{
				kill(philo[i]->pid, 15);
				i++;
			}
		}
		else
			printf("error\n");
		i++;
	}
}

static int	simulation(t_philo **philo)
{
	int i;
	int pid;

	i = -1;
	set_time(&philo[0]->program->start);
	while (++i < philo[0]->program->nbr_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo[i]->last_meal = philo[i]->program->start;
			routine(philo[i]);
			exit(0);
		}
		else if (pid < 0)
			return (error_msg(FORK_ERROR));
		philo[i]->pid = pid;
		i++;
	}
}

int main(int ac, char *av[])
{
	t_program 	program;
	t_philo 	**philo;

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
	if (simulation(philo) == 1)
	{
		free_program(philo[0]->program);
		return (EXIT_FAILURE);
	}
	free_program(philo[0]->program);
	return (EXIT_SUCCESS);
}
