/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/02 07:40:07 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
}

void	simulation_init(t_program *program, char **argv, int argc)
{
	program = malloc(sizeof(t_program) * 1);
	program->nbr_philo = (int) ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->meals = 1;
	program->philo = malloc(sizeof(t_philo) * program->nbr_philo);
	program->philo = philo_init(program);	
}

t_philo	*philo_init(t_program *program)
{
	int		n;

	n = 0;
	while()
		
}

/* ./philo number_of_philo time_to_die time_to_eat time_to_sleep [number eats] */
int main(int argc, char *argv[])
{
	t_program 	program;
	if (argc != 5 && argc != 6)
		error_msg(FEW_ARG);
	Validation(); //ver se tudo eh numero
	simulation_init(program, argv, argc);
	simulation(prgram);
	//free a tudo
}
