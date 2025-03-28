/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guardians.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:08:10 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/28 20:00:51 by rd-agost         ###   ########.fr       */
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
		ft_error("Mutex Error, wrong opcode");
}

//error proofified thread op, wwraaah
static void	ft_thread_guard(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	else if (status == EINVAL && opcode == CREATE)
		ft_error("Invalid settings in attr");
	else if (status == EINVAL && (opcode == DETACH || opcode == JOIN))
		ft_error("thread is not a joinable thread");
	else if (status == EPERM)
		ft_error("No permission to set the sched policy & params (attr err)");
	else if (status == ESRCH)
		ft_error("No thread with the ID thread could be found");
	else if (status == EDEADLK)
		ft_error("A  deadlock  was  detected");
}

/* 
void *(*foo)(void *)
"foo è un puntatore a funzione che accetta un void * come 
parametro e restituisce un void * come risultato."
kinda a callback, questa AsciiArt la uso perch non so il tipo del val di ritorno
*/
void	ft_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		ft_thread_guard(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		ft_thread_guard(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		ft_thread_guard(pthread_detach(*thread), opcode);
	else
		ft_error("Thread Error, wrong opcode");
}