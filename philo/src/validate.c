/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:41:02 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/28 02:49:51 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	if_is_a_number(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return (1);
	if (str[i] == '-' )
		return (error_msg(NEG_ARG));
	if (str[i] == '+' || str[i] == '0')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (error_msg(NOT_NBR));
		i++;
	}
	return (0);
}

static int	safe_program(char **av, int ac)
{
	if (ft_atoi(av[1]) > INT_MAX)
		return (error_msg(TOO_MANY_PHILO));
	if (ac == 6 && ft_atoi(av[5]) > INT_MAX)
		return (error_msg(TOO_BIG_MEALS));
	if (ft_atoi(av[2]) >= LONG_MAX || ft_atoi(av[3]) >= LONG_MAX
		|| ft_atoi(av[4]) >= LONG_MAX)
		return (error_msg(TOO_BIG));
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
		return (error_msg(TOO_SMALL));
	if (ac == 6 && ft_atoi(av[5]) < 1)
		return (error_msg(TOO_SMALL_MEALS));
	return (0);
}

int	validate_args(char **av, int ac)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (if_is_a_number(av[i]))
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		printf("WARNING: too many Philosophers.\n");
	if (safe_program(av, ac) == 1)
		return (0);
	return (1);
}
