/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:41:02 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/16 19:52:28 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int if_is_a_number(char *str)
{
	int		i;

	i = 0;

	if (!str[i])
		return (0);
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
	return (1);
}

int	validate_args(char **argv, int argc)
{
	int		i;
	
	i = 1;
	while (i < argc)
	{
		if(!if_is_a_number(argv[i]))
			return (0);
		i++;
	}
	if (atoi(argv[1]) > 200)
		printf("WARNING: too many Philosophers.\n");
	return (1);
}