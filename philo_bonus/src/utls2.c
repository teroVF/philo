/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:16:51 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/30 23:09:44 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	if (ft_strcmp(error_msg, FEW_ARG) == 0)
	{
		ft_putstr_fd("Usage: ./philo number_of_philo", STDERR_FILENO);
		ft_putstr_fd("time_to_die time_to_eat ", STDERR_FILENO);
		ft_putendl_fd("time_to_sleep [number eats]", STDERR_FILENO);
	}
	return (1);
}

void	print_msg(t_philo *philo, char *msg)
{
	struct timeval	time;

	sem_wait(philo->program->write);
	if (philo->m_stop == 1)
	{
		sem_post(philo->program->write);
		return ;
	}
	set_time(&time);
	if (strcmp(msg, DEAD) == 0)
	{
		printf(msg, 
			deltatime(philo->program->start, time), philo->sit);
		philo->m_stop = 1;
		return ;
	}
	else
		printf(msg, 
			deltatime(philo->program->start, time), philo->sit);
	sem_post(philo->program->write);
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
	if (ft_strlen(str) > 19)
		return (9223372036854775807);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * sinal);
}
