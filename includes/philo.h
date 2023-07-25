/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/24 23:37:05 by anvieira         ###   ########.fr       */
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
# include "log_msg.h"

# define EVEN(x) (!(x % 2)	? true : false)

typedef struct	s_philo
{
	bool				dead;
	bool				even;
	bool				eating;
	bool				is_full;
	int					sit;
	int					numb_meals;
	struct s_program	*program;
	pthread_t			*tid;
	time_t				last_meal;
}				t_philo;

typedef struct s_program
{	
	pthread_t		*check_time;
	int				someone_dead;
	int				nbr_philo;
	int				meals;
	int				count_philo;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*time;
	pthread_mutex_t	*write;
	t_philo			**philo;
	time_t			start;
	time_t			time_sleep;
	time_t			time_eat;
	time_t			time_die;
}					t_program;

int			simulation_init(t_program *program, char **argv, int argc);
int			validate_args(char **argv, int argc);
int			error_msg(char *error_msg);
void    	*routine(void *pointer);
void		free_program(t_program *program);

/* TIME */
void    	ft_usleep(time_t mi_s);
time_t   	check_time(time_t start);

/* UTLS */
time_t		ft_atoi(const char *str);
void    	ft_putendl_fd(char *s, int fd);
void    	ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
void		print_msg(t_philo *philo, char *msg);

/* MUTEX INIT AND FREE */
int		mutex_init(t_program *program);
void   *is_dead(void *arg);

#endif