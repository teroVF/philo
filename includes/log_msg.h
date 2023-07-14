/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_msg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:53:52 by antero            #+#    #+#             */
/*   Updated: 2023/07/14 02:24:17 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

/* ERROR MESSAGES */
/* arguments validation errors*/
# define FEW_ARG "Few Arguments."
# define NOT_NBR "All arguments should be a number"
# define NEG_ARG "All arguments should be positive"
# define BIG_ARG "Argument too big"
# define BIG_NBR "Number too big"
# define MALLOC_ERROR "Malloc error"
# define CREATE_THREAD_ERROR "Error creating thread"
# define MUTEX_INIT_ERROR "Error initializing mutex"

/* PHILO ACTIONS */
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define FORK "has taken a fork"
# define DEAD "is dead"

#endif