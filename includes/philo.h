/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:35:31 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/16 19:47:46 by anvieira         ###   ########.fr       */
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
# include "log_msg.h"

# define EVEN(x) (!(x % 2)	? true : false)

typedef struct	s_philo
{
	pthread_t			*tid;
	int					sit;
	int					numb_meals;
	bool				is_full;
	bool				even;
	time_t			last_meal;
	bool				dead;
	struct s_program	*program;
}				t_philo;

typedef struct s_program
{	
	t_philo			**philo;
	int				nbr_philo;
	time_t		time_die;
	time_t		time_eat;
	time_t		time_sleep;
	time_t		start;
	int				meals;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*time;
	pthread_mutex_t	*write;
	int				someone_dead;
}				t_program;

void		simulation_init(t_program *program, char **argv, int argc);
int			validate_args(char **argv, int argc);
int			error_msg(char *error_msg);
void    	*routine(void *pointer);
void		free_everything(t_program *program);

/* TIME */
void    	ft_usleep(time_t mi_s);
time_t   check_time(time_t start);

/* UTLS */
time_t	ft_atoi(const char *str);
void    	ft_putendl_fd(char *s, int fd);
void    	ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
void		print_msg(t_philo *philo, char *msg);

/* MUTEX INIT AND FREE */
void		mutex_init(t_program *program);

#endif