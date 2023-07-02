/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:41:02 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/09 13:41:45 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int if_is_a_number(char *str)
{
	int		i;

	i = 0;

	if (!str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
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
	printf("perfeito\n");
}