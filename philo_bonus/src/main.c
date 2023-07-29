/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/29 03:52:58 by anvieira         ###   ########.fr       */
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
void	*monitorizing_food (void *arg)
{
	int flag_all_eat;
	int i;
	t_program *program;

	printf("monitorizing_food\n");
	flag_all_eat = 0;
	i = 0;
	program = (t_program *)arg;
	while(1)
	{
		sem_wait(program->eat);
		flag_all_eat++;
		if (flag_all_eat == program->nbr_philo)
		{
			while (i < program->nbr_philo)
			{
				kill(program->philo[i]->pid, 15);
				i++;
				break;
			}
		}
	}
	return (NULL);
}


void *exit_program(void *arg)
{
	int i;
	int status;
	t_program *program;
	
	printf("exit_program\n");
	program = (t_program *)arg;
	i = 0;
	while (i < program->nbr_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			while (i < program->nbr_philo)
			{
				kill(program->philo[i]->pid, 15);
				i++;
			}
		}
		i++;
	}
	return (NULL);
}

static int	simulation(t_philo **philo)
{
	int i;
	int pid;

	i = -1;
	set_time(&(philo[0]->program->start));
	while (++i < philo[0]->program->nbr_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo[i]->last_meal = philo[i]->program->start;
			routine(philo[i]);
		}
		else if (pid < 0)
			return (error_msg(FORK_ERROR));
		philo[i]->pid = pid;
		i++;
	}
	printf("simulation\n");
	pthread_create(&philo[0]->program->moni_food, NULL, monitorizing_food, philo[0]->program);
	pthread_create(&philo[0]->program->moni_dead, NULL, exit_program, philo[0]->program);
	return (0);
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
	if (simulation_init(&program, av, ac) == 1)
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
	void *status = NULL;
	
	pthread_join(philo[0]->program->moni_dead, status);
	pthread_join(philo[0]->program->moni_food, status);
	if (status == 0)
		printf("todos comeram\n");
	else
		printf("alguem morreu\n");
	free_program(philo[0]->program);
	return (EXIT_SUCCESS);
}
