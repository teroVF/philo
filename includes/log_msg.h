/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_msg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:53:52 by antero            #+#    #+#             */
/*   Updated: 2023/07/16 20:21:48 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

/* ERROR MESSAGES */
/* arguments validation errors*/
# define FEW_ARG "Few Arguments."
# define NOT_NBR "All arguments should be a number"
# define NEG_ARG "All arguments should be positive"
# define MANY_ARG "Many Arguments"
# define MALLOC_ERROR "Malloc error"
# define CREATE_THREAD_ERROR "Error creating thread"
# define MUTEX_ERROR_FORK "Error creating mutex for fork"
# define MUTEX_ERROR_DEAD "Error creating mutex for dead"
# define MUTEX_ERROR_WRITE "Error creating mutex for write"
# define MUTEX_ERROR_EATING "Error creating mutex for eating"
# define JOIN_THREAD_ERROR "Error joining thread"
# define ALL_ARGUMENTS "./PHILONBR NBR_PHILOSOPHERS TIME_TO_DIE TIME_TO_EAT TIME_TO_SLEEP [NBR_MEALS]"

/* PHILO ACTIONS */
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORK "has taken a fork"
# define LEAVE_FORK "has left a fork"
# define DEAD "is dead"
# define I_AM_ALONE "will die alone. You bastard!"

#endif