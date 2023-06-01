/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/01 01:50:48 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include "error_msg.h"

typedef struct s_program
{
    t_philo				*philo;
	__int64_t		time_die;
	__int64_t		time_eat;
	__int64_t		time_sleep;
}				t_program;

typedef struct	s_philo
{
    int		pos;
	bool	even;
	bool	fork;
	int		numb_meals;
	t_philo next;
	t_philo previous;
	
}				t_philo;

void    ft_usleep(__ino64_t up)

#endif