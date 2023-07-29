/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/29 03:33:44 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
# include <limits.h>
# include "log_msg.h"
# include "log_msg_bonus.h"

typedef struct	s_philo
{
	pthread_t			check_events;
	pthread_mutex_t		stop;
	bool				m_stop;
	int					pid;
	bool				even;
	bool				eating;
	int					sit;
	int					numb_meals;
	struct timeval		last_meal;
	bool				is_full;
	bool				dead;
	struct s_program	*program;
}				t_philo;

typedef struct s_program
{	
	int				someone_dead;
	int				nbr_philo;
	int				meals;
	int				count_philo;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*dead;
	sem_t			*eat;
	pthread_t		moni_food;
	pthread_t		moni_dead;
	struct timeval	start;
	t_philo			**philo;
	time_t			time_sleep;
	time_t			time_eat;
	time_t			time_die;
}					t_program;

int			simulation_init(t_program *program, char **argv, int argc);
int			validate_args(char **argv, int argc);
int			error_msg(char *error_msg);
int			routine(t_philo *philo);
void		free_program(t_program *program);

/* TIME */


/* UTLS */
time_t		ft_atoi(const char *str);
void    	ft_putendl_fd(char *s, int fd);
void    	ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
void		print_msg(t_philo *philo, char *msg);

/* MUTEX INIT AND FREE */
int		semaph_init(t_program *program);
time_t	deltatime(struct timeval t0, struct timeval t1);
int	set_time(struct timeval *t);

#endif