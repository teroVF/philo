/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/06/08 02:49:42 by anvieira         ###   ########.fr       */
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


typedef struct	s_philo
{
	pthread_t			thread;
	int					pos;
	bool				even;
	int					numb_meals;
	__uint64_t			last_meal;
	struct s_program	*program;
}				t_philo;

typedef struct s_program
{	
	t_philo			**philo;
	int				nbr_philo;
	__uint64_t		time_die;
	__uint64_t		time_eat;
	__uint64_t		time_sleep;
	__uint64_t		start;
	__uint64_t		starve;
	int				meals;
	pthread_mutex_t *mutex_fork;
	pthread_mutex_t mutex_cronos;
}				t_program;

// void    ft_usleep(__int64_t mi_s);
__uint64_t	ft_atoi(const char *str);
void    ft_putendl_fd(char *s, int fd);

#endif