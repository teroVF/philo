/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_msg_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:53:52 by antero            #+#    #+#             */
/*   Updated: 2023/07/30 23:09:13 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_MSG_BONUS_H
# define LOG_MSG_BONUS_H

/* COLORS */
# define DEF "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

/* ERROR MESSAGES */
# define FEW_ARG RED"Few Arguments."DEF
# define TOO_SMALL RED"All time arguments should be greater than 60"DEF
# define TOO_BIG RED"All time arguments should be Less than LONG_MAX"DEF
# define TOO_BIG_MEALS RED"Meals argument should be Less than INT_MAX"DEF
# define TOO_MANY_PHILO RED"Too many Philosophers. Max: MAX_INT"DEF
# define TOO_SMALL_MEALS RED"Meals argument should be greater than 0"DEF
# define NOT_NBR RED"All arguments should be a number"DEF
# define NEG_ARG RED"All arguments should be positive"DEF
# define MANY_ARG RED"Many Arguments"DEF
# define MALLOC_ERROR RED"Malloc error"DEF
# define CREATE_THREAD_ERROR RED"Error creating thread"DEF
# define MUTEX_ERROR_FORK RED"Error creating mutex for fork"DEF
# define MUTEX_ERROR_STOP RED"Error creating mutex for stop"DEF
# define MUTEX_ERROR_WRITE RED"Error creating mutex for write"DEF
# define JOIN_THREAD_ERROR RED"Error joining thread"DEF
# define ALL_ARGUMENTS RED"./PHILONBR NBR_PHILOSOPHERS \
TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP [NBR_MEALS]"DEF
# define FORK_ERROR RED"Error creating fork"DEF
# define SEM_ERROR_FORK RED"Error creating semaphore for fork"DEF

/* PHILO ACTIONS */
# define EATING MAGENTA"%lu %d is eating\n"DEF
# define SLEEPING CYAN"%lu %d is sleeping\n"DEF
# define THINKING WHITE"%lu %d is thinking\n"DEF
# define FORK YELLOW"%lu %d has taken a fork\n"DEF
# define DEAD RED"%lu %d died\n"DEF
# define FALSE 0
# define TRUE  1

#endif