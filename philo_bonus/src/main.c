/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/26 04:15:53 by anvieira         ###   ########.fr       */
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

static void	simulation(t_philo **philo)
{
	int i;
	int pid;

	i = 0;
	philo[0]->program->start = check_time(0);
	while (i < philo[0]->program->nbr_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			routine(philo[i]);
			exit(0);
		}
		else if (pid < 0)
			error_msg(FORK_ERROR);
		philo[i]->pid = pid;
		i++;
	}
	exit_program(philo);

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
	data(&program);
	simulation(philo);
	sem_wait(program.write);
	sem_post(program.write);
	free_program(&program);
	kill(0, 2);
	return (EXIT_SUCCESS);
}
