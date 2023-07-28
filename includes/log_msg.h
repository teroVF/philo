/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_msg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:23:55 by anvieira          #+#    #+#             */
/*   Updated: 2023/07/28 03:25:53 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_MSG_H
# define LOG_MSG_H

/* ERROR MESSAGES */
/* arguments validation errors*/
# define FEW_ARG "Few Arguments."
# define TOO_SMALL "All time arguments should be greater than 60"
# define TOO_BIG "All time arguments should be Less than LONG_MAX"
# define TOO_BIG_MEALS "Meals argument should be Less than INT_MAX"
# define TOO_MANY_PHILO "Too many Philosophers. Max: MAX_INT"
# define TOO_SMALL_MEALS "Meals argument should be greater than 0"
# define NOT_NBR "All arguments should be a number"
# define NEG_ARG "All arguments should be positive"
# define MANY_ARG "Many Arguments"
# define MALLOC_ERROR "Malloc error"
# define CREATE_THREAD_ERROR "Error creating thread"
# define MUTEX_ERROR_FORK "Error creating mutex for fork"
# define MUTEX_ERROR_STOP "Error creating mutex for stop"
# define MUTEX_ERROR_WRITE "Error creating mutex for write"
# define JOIN_THREAD_ERROR "Error joining thread"
# define ALL_ARGUMENTS "./PHILONBR NBR_PHILOSOPHERS \
TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP [NBR_MEALS]"

/* PHILO ACTIONS */
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORK "has taken a fork"
# define DEAD "died"
# define FULL "is full"
# define I_AM_ALONE "will die alone. You bastard!"
# define AQUI_VOU_EU "aqui vou eu"
# define FALSE 0
# define TRUE  1

#endif