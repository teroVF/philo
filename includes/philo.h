/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/28 03:27:26 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include "log_msg.h"

typedef struct s_philo
{
	bool				even;
	bool				is_full;
	int					sit;
	int					numb_meals;
	struct s_program	*program;
	struct timeval		last_meal;
	pthread_t			tid;
}				t_philo;

typedef struct s_program
{
	int				stop;
	int				someone_dead;
	int				nbr_philo;
	int				meals;
	int				count_philo;
	pthread_t		check_time;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	write;
	pthread_mutex_t	m_stop;
	time_t			time_die;
	time_t			time_sleep;
	time_t			time_eat;
	struct timeval	start;
	t_philo			**philo;
}					t_program;

/* Validation */
int			validate_args(char **argv, int argc);

/* Funtion to check if philo died or all ate */
void		*monitor(void *arg);

/* Funtion related to philo */
void		*routine(void *pointer);

/* Time */
time_t		deltatime(struct timeval t0, struct timeval t1);
int			set_time(struct timeval *t);

/* Utls */
void		print_msg(t_philo *philo, char *msg);
int			error_msg(char *error_msg);
time_t		ft_atoi(const char *str);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(const char *str);

/* Init */
int			simulation_init(t_program *program, char **argv, int argc);
int			mutex_init(t_program *program);

/* Free */
void		free_program(t_program *program);

#endif