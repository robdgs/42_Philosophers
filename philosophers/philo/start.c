/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:05:15 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/21 18:06:55 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_start_single_philo(t_container *container,
	pthread_t *monitor_thread)
{
	ft_thread_handle(&container->philos[0].thread_id, ft_simulation,
		&container->philos[0], CREATE);
	ft_thread_handle(monitor_thread, ft_monitor, container, CREATE);
	container->start_simulation = ft_get_time(MILLISEC);
	ft_set_long(&container->philos[0].philo_mutex,
        &container->philos[0].lmeal_time, container->start_simulation);
	ft_set_bool(&container->container_mtx, &container->sync, true);
	ft_thread_handle(&container->philos[0].thread_id, NULL, NULL, JOIN);
	ft_thread_handle(monitor_thread, NULL, NULL, JOIN);
}

static void	ft_start_multi_philo(t_container *container,
	pthread_t *monitor_thread)
{
	int	i;

	container->start_simulation = ft_get_time(MILLISEC);
	i = -1;
	while (++i < container->hm_philos)
    	ft_set_long(&container->philos[i].philo_mutex,
        &container->philos[i].lmeal_time, container->start_simulation);
	ft_set_bool(&container->container_mtx, &container->sync, true);
	i = -1;
	while (++i < container->hm_philos)
		ft_thread_handle(&container->philos[i].thread_id, ft_simulation,
			&container->philos[i], CREATE);
	ft_thread_handle(monitor_thread, ft_monitor, container, CREATE);
	i = -1;
	while (++i < container->hm_philos)
		ft_thread_handle(&container->philos[i].thread_id, NULL, NULL, JOIN);
	ft_thread_handle(monitor_thread, NULL, NULL, JOIN);
}

void	ft_start(t_container *container)
{
	pthread_t	monitor_thread;

	if (container->max_meals == 0)
		return ;
	if (container->hm_philos == 1)
		ft_start_single_philo(container, &monitor_thread);
	else
		ft_start_multi_philo(container, &monitor_thread);
	ft_clean(container);
}
