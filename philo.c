/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:30:16 by anvieira          #+#    #+#             */
/*   Updated: 2023/05/31 02:22:33 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
}

/* ./philo number_of_philo time_to_die time_to_eat time_to_sleep [number eats] */
int main(int argc, char const *argv[])
{
	if (argc < 5 )
		error_msg(FEW_ARG);
	
}
