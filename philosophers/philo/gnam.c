/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:14:44 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/27 18:41:01 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//input: ./philo 5 800 200 200 [5] 
//[n of philo, time to die, time to eat, time to nap, number of meals(optional)]
/* 
flow:
1. if no meal, return (last param == 0)
1.1 if ONLY 1 philo -> gestire separatamente
2. creare i thread, creare i philos
3. creare un thread che monitora se muore qualcuno
4. sincronizza l'inizio: tutti i filosofi devono iniziare la simulazione 
contemporaneamente e non all'immediata creazione del thread
5. join tutti 
*/

bool	ft_isfinished(t_container *container)
{
	return(ft_get_bool(&container->container_mtx, &container->end_sim));
}

void	*ft_simulation(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	ft_synchronizer(philo->container);

	return NULL;
}

void	ft_start(t_container *container)
{
	int	i;

	i = -1;
	
	if(container->max_meals == 0)
		return;
	else if (container->hm_philos == 1)
		;//funz x gestire a parte, todo
	else
		{
			while(++i < container->hm_philos)
				ft_thread_handle(&container->philos[i].thread_id, ft_simulation,
					&container->philos[i], CREATE);
		}
	ft_set_bool(&container->container_mtx, &container->sync, true);
}
