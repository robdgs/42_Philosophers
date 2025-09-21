/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:22:30 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/21 18:23:57 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;
	long	last_meal;

	if (ft_get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	last_meal = ft_get_long(&philo->philo_mutex, &philo->lmeal_time);
	if (last_meal <= 0)
		return (false);
	elapsed = ft_get_time(MILLISEC) - last_meal;
	time_to_die = philo->container->time_to_die;
	if (elapsed < 0)
		return (false);
	return (elapsed >= (time_to_die + 1));
}

static bool	ft_all_full(t_container *container)
{
	int	i;
	int	full_count;

	if (container->max_meals == -1)
		return (false);
	i = -1;
	full_count = 0;
	while (++i < container->hm_philos)
	{
		if (ft_get_bool(&container->philos[i].philo_mutex,
				&container->philos[i].is_full))
			full_count++;
	}
	return (full_count == container->hm_philos);
}

void	*ft_monitor(void *data)
{
	t_container	*container;
	int			i;

	container = (t_container *)data;
	while (!ft_isfinished(container))
	{
		i = -1;
		while (++i < container->hm_philos && !ft_isfinished(container))
		{
			if (ft_philo_died(&container->philos[i]))
			{
				ft_print_status(DEAD, &container->philos[i]);
				ft_set_bool(&container->container_mtx,
					&container->end_sim, true);
				return (NULL);
			}
		}
		if (ft_all_full(container))
		{
			ft_set_bool(&container->container_mtx, &container->end_sim, true);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
