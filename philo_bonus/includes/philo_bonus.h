/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/30 23:17:18 by anvieira         ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include "log_msg_bonus.h"

typedef struct s_philo
{
	pthread_t			check_events;
	bool				m_stop;
	int					pid;
	int					sit;
	int					numb_meals;
	struct timeval		last_meal;
	struct s_program	*program;
}						t_philo;

typedef struct s_program
{
	int				nbr_philo;
	int				meals;
	int				count_philo;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*dead;
	sem_t			*eat;
	int				moni_food;
	struct timeval	start;
	t_philo			**philo;
	time_t			time_sleep;
	time_t			time_eat;
	time_t			time_die;
}					t_program;

/* Validation */
int			validate_args(char **argv, int argc);

/* each philo */
int			routine(t_philo *philo);

/* Funtion to check if philo died*/
void		*monitor(void *arg);

/* time */
time_t		deltatime(struct timeval t0, struct timeval t1);
int			set_time(struct timeval *t);

/* utls */
int			error_msg(char *error_msg);
void		print_msg(t_philo *philo, char *msg);
time_t		ft_atoi(const char *str);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(const char *str);

/* init and free */
int			simulation_init(t_program *program, char **argv, int argc);
int			semaph_init(t_program *program);
void		free_program(t_program *program);

#endif