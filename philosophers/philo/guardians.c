/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guardians.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:08:10 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/24 19:23:04 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// self-checking functions 
//DON'T EVER START THE ROUTINE BFORE EVERYTHING IS CHECKED!!
void	*ft_malloc(size_t bytes)
{
	void	*allocated;
	
	allocated = malloc(bytes);
	if (!allocated && ft_error("Malloc Error"))
		return NULL;
	return allocated;
}

//error proofified mutex, wwraaah
static void	ft_mutex_guard(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK 
			||opcode == DESTROY))
		ft_error("Invalid value by mutex");
	else if (status == EINVAL && opcode == INIT)
		ft_error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		ft_error("deadlock!");
	else if (status == EPERM)
		ft_error("current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		ft_error("Not enough mem to create another mutex");
	else if (status == EBUSY)
		ft_error("the mutex is locked");	
}

void	ft_mutex_caller(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		ft_mutex_guard(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		ft_mutex_guard(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		ft_mutex_guard(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		ft_mutex_guard(pthread_mutex_destroy(mutex), opcode);
	else 
		ft_mutex_guard(ft_error("Mutex Error, wrong opcode"), opcode);
}

void	ft_thread_guard(int status, t_opcode opcode)
{
	
}
