/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:22:54 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/14 01:30:48 by anvieira         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

__uint64_t	ft_atoi( const char *str)
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

int ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
        write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
        if (!s)
                return ;
        while (*s != '\0')
                ft_putchar_fd(*(s++), fd);
        ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}