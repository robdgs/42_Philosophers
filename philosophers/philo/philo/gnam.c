/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:14:44 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/20 13:34:53 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//input: ./philo 5 800 200 200 [5] 
//[n of philo, time to die, time to eat, time to nap, number of meals(optional)]
bool	ft_isfinished(t_container *container)
{
	return (ft_get_bool(&container->container_mtx, &container->end_sim));
}

static void	ft_think(t_philo *philo)
{
	ft_print_status(THINKING, philo);
}

void	ft_gnam(t_philo *philo)
{
	if (philo->container->hm_philos == 1)
	{
		ft_mutex_caller(&philo->f_fork->fork, LOCK);
		ft_print_status(TAKING_FORK, philo);
		// Can't eat with only one fork, so just wait and die
		ft_secured_usleep(philo->container->time_to_die * 1000, philo->container);
		ft_mutex_caller(&philo->f_fork->fork, UNLOCK);
		return;
	}
	ft_mutex_caller(&philo->f_fork->fork, LOCK);
	ft_print_status(TAKING_FORK, philo);
	ft_mutex_caller(&philo->s_fork->fork, LOCK);
	ft_print_status(TAKING_FORK, philo);
	ft_set_long(&philo->philo_mutex, &philo->lmeal_time, ft_get_time(MILLISEC));
	philo->hm_meals++;
	ft_print_status(EATING, philo);
	ft_secured_usleep(philo->container->time_to_eat * 1000, philo->container);
	if (philo->container->max_meals > 0
		&& philo->hm_meals == philo->container->max_meals)
		ft_set_bool(&philo->philo_mutex, &philo->is_full, true);
	ft_mutex_caller(&philo->f_fork->fork, UNLOCK);
	ft_mutex_caller(&philo->s_fork->fork, UNLOCK);
}

void	*ft_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!philo)
	{
		printf("[ERROR] Philo struct is NULL\n");
		return (NULL);
	}
	ft_synchronizer(philo->container);
	ft_set_long(&philo->philo_mutex, &philo->lmeal_time, ft_get_time(MILLISEC));
	if (philo->philo_id % 2 == 0)
		ft_secured_usleep(15000, philo->container);
	while (!ft_isfinished(philo->container))
	{
		if (ft_get_bool(&philo->philo_mutex, &philo->is_full))
			break ;
		ft_gnam(philo);
		if (ft_isfinished(philo->container))
			break ;
		ft_print_status(SLEEPING, philo);
		ft_secured_usleep(philo->container->time_to_nap * 1000, philo->container);
		if (ft_isfinished(philo->container))
			break ;
		ft_think(philo);
	}
	return (NULL);
}

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

void	ft_start(t_container *container)
{
	int			i;
	pthread_t	monitor_thread;

	if (container->max_meals == 0)
		return ;
	
	i = -1;
	while (++i < container->hm_philos)
		ft_thread_handle(&container->philos[i].thread_id, ft_simulation,
			&container->philos[i], CREATE);
	ft_thread_handle(&monitor_thread, ft_monitor, container, CREATE);
	container->start_simulation = ft_get_time(MILLISEC);
	ft_set_bool(&container->container_mtx, &container->sync, true);
	i = -1;
	while (++i < container->hm_philos)
		ft_thread_handle(&container->philos[i].thread_id, NULL, NULL, JOIN);
	ft_thread_handle(&monitor_thread, NULL, NULL, JOIN);
}
