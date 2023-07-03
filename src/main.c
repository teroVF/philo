/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:42:18 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/03 17:09:39 by anvieira         ###   ########.fr       */
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

// static void	simulation(t_philo **philo)
// {
// 	int n;
// 	n = 0;
// 	while (n < philo[0]->program->nbr_philo)
// 	{
// 		if(philo[n]->even == 1)
// 			pthread_create(&(philo[n]->thread), NULL, como_peixe, NULL);
// 		else if(philo[n]->even == 0)
// 			pthread_create(&(philo[n]->thread), NULL, como_galinha, NULL);
// 		n++;
// 	}
// 	for (int i = 0; i < philo[0]->program->nbr_philo; i++)
//     {
//         pthread_join(philo[i]->thread, NULL);
//     }
// }

int main(int ac, char *av[])
{
	t_program 	program;
	
	(void) program;
	if (ac != 5 && ac != 6)
		error_msg(FEW_ARG);	
	validation(av, ac);
	// simulation_init(&program, argv, argc);
	// simulation(program);
	//free a tudo
}
