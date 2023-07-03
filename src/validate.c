/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:41:02 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/03 17:09:27 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int if_is_a_number(char *str)
{
	int		i;

	i = 0;

	if (!str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-' || str[i] == '0')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

void	validation(char **argv, int argc)
{
	int		i;
	
	i = 1;
	while (i < argc)
	{
		if(!if_is_a_number(argv[i]))
			error_msg(NOT_NBR);
		i++;
	}
	if	(atoi(argv[1]) < 2)
		ft_putstr_fd("WARNING: 1 Philosopher .\n", 1);
	else if (atoi(argv[1]) > 200)
		ft_putstr_fd("WARNING: too many Philosophers.\n", 1);
}