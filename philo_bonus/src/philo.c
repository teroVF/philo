/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/30 00:03:25 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo			*philo;
	struct timeval	time;
	int				flag;

	philo = (t_philo *)arg;
	flag = 0;
	while (1)
	{
		sem_wait(philo->program->dead);
		set_time(&time);
		if (deltatime(philo->last_meal, time) > philo->program->time_die)
		{
			print_msg(philo, DEAD);
			exit(1);
		}
		sem_post(philo->program->dead);
		sem_wait(philo->program->dead);
		if (philo->program->meals != -1 
			&& philo->numb_meals == philo->program->meals && !flag++)
			sem_post(philo->program->eat);
		sem_post(philo->program->dead);
	}
	return (NULL);
}

void	destroy_sem(t_program *program)
{
	sem_close(program->forks);
	sem_close(program->write);
	sem_close(program->dead);
	sem_close(program->eat);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("dead");
	sem_unlink("eat");
}

void	free_program(t_program *program)
{
	int	i;
	int	n;

	i = -1;
	n = program->nbr_philo;
	destroy_sem(program);
	i = -1;
	while (++i < n)
		free(program->philo[i]);
	free(program->philo);
}

t_philo	*philo_init(t_program *program, int n)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		error_msg(MALLOC_ERROR);
	philo->sit = n + 1;
	philo->is_full = FALSE;
	philo->dead = FALSE;
	philo->m_stop = FALSE;
	philo->program = program;
	if (program->meals != -1)
		philo->numb_meals = 0;
	else
		philo->numb_meals = -1;
	return (philo);
}

int	simulation_init(t_program *program, char **argv, int argc)
{
	int		n;

	n = -1;
	program->nbr_philo = (int)ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	program->meals = -1;
	if (argc == 6)
		program->meals = (int) ft_atoi(argv[5]);
	program->philo = malloc(sizeof(t_philo *) * program->nbr_philo);
	if (program->philo == NULL)
		return (error_msg(MALLOC_ERROR));
	while (++n < program->nbr_philo)
		program->philo[n] = philo_init(program, n);
	if (semaph_init(program) == 0)
		return (1);
	return (0);
}
