/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:27:53 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/27 18:42:51 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//spinlock
/* In informatica uno spinlock o anche spinning è una tecnica di 
programmazione che utilizza un ciclo di attesa attiva (busy waiting) per 
implementare la routine di attesa di un lock. La tecnica consiste nel 
verificare periodicamente se il lock è stato sbloccato, effettuando un 
test che può aver luogo ad intervalli di tempo prestabiliti, oppure nel 
tempo più breve possibile consentito dal sistema. */
void	ft_synchronizer(t_container	*container)
{
	while(!ft_get_bool(&container->container_mtx, &container->sync))
		;
}

void	ft_set_bool(t_mutex *mutex, bool *dest, bool val)
{
	ft_mutex_caller(mutex, LOCK);
	*dest = val;
	ft_mutex_caller(mutex, UNLOCK);
}

bool	ft_get_bool(t_mutex *mutex, bool *val)
{
	bool	ret;
	
	ft_mutex_caller(mutex, LOCK);
	ret = *val;
	ft_mutex_caller(mutex, UNLOCK);
	return(ret);
}

int	ft_set_int(t_mutex *mutex, int *dest, int val)
{
	ft_mutex_caller(mutex, LOCK);
	*dest = val;
	ft_mutex_caller(mutex, UNLOCK);
}

int	ft_get_int(t_mutex *mutex, int *val)
{
	int	ret;
	
	ft_mutex_caller(mutex, LOCK);
	ret = *val;
	ft_mutex_caller(mutex, UNLOCK);
	return(ret);
}