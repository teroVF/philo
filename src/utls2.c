/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 04:14:09 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/20 04:17:22 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (ft_strcmp(error_msg, FEW_ARG) == 0)
	{
		ft_putstr_fd("Usage: ./philo number_of_philo", STDERR_FILENO);
		ft_putstr_fd("time_to_die time_to_eat ", STDERR_FILENO);
		ft_putendl_fd("time_to_sleep [number eats]\n", STDERR_FILENO);
	}
	return (0);
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->program->write);
	if (philo->program->someone_dead == false)
		printf("%lu, the philo n %d %s\n",
			check_time(philo->program->start), philo->sit, msg);
	else if (philo->dead == true)
		printf("%lu, the philo n %d %s\n",
			check_time(philo->program->start), philo->sit, DEAD);
	pthread_mutex_unlock(philo->program->write);
}

time_t	ft_atoi( const char *str)
{
	int		i;
	int		sinal;
	long	num;

	num = 0;
	sinal = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sinal *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * sinal);
}
