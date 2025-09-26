/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:14:44 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/26 20:40:24 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isfinished(t_container *container)
{
	return (ft_get_bool(&container->container_mtx, &container->end_sim));
}

void	ft_think(t_philo *philo)
{
	long	think_time;

	think_time = 0;
	ft_print_status(THINKING, philo);
	if (philo->container->hm_philos % 2 == 1)
	{
		think_time = (philo->container->time_to_eat * 2)
			- philo->container->time_to_nap;
		if (think_time < 0)
			think_time = 1;
		if (think_time > philo->container->time_to_die / 3)
			think_time = philo->container->time_to_die / 3;
		ft_secured_usleep(think_time * 1000, philo->container);
	}
	else
		ft_secured_usleep(1000, philo->container);
}

void	ft_gnam(t_philo *philo)
{
	long	eat_start;

	ft_mutex_caller(&philo->f_fork->fork, LOCK);
	ft_print_status(TAKING_FORK, philo);
	if (philo->container->hm_philos == 1)
	{
		ft_secured_usleep(philo->container->time_to_die * 1000,
			philo->container);
		ft_mutex_caller(&philo->f_fork->fork, UNLOCK);
		return ;
	}
	ft_mutex_caller(&philo->s_fork->fork, LOCK);
	ft_print_status(TAKING_FORK, philo);
	eat_start = ft_get_time(MILLISEC);
	ft_set_long(&philo->philo_mutex, &philo->lmeal_time, eat_start);
	ft_mutex_caller(&philo->philo_mutex, LOCK);
	philo->hm_meals++;
	ft_mutex_caller(&philo->philo_mutex, UNLOCK);
	ft_print_status(EATING, philo);
	ft_secured_usleep(philo->container->time_to_eat * 1000, philo->container);
	if (philo->container->max_meals > 0 && ft_get_long(&philo->philo_mutex,
			&philo->hm_meals) >= philo->container->max_meals)
		ft_set_bool(&philo->philo_mutex, &philo->is_full, true);
	ft_mutex_caller(&philo->f_fork->fork, UNLOCK);
	ft_mutex_caller(&philo->s_fork->fork, UNLOCK);
}

static void	ft_philo_routine(t_philo *philo)
{
	while (!ft_isfinished(philo->container))
	{
		if (ft_get_bool(&philo->philo_mutex, &philo->is_full))
			break ;
		ft_gnam(philo);
		if (ft_isfinished(philo->container))
			break ;
		ft_print_status(SLEEPING, philo);
		ft_secured_usleep(philo->container->time_to_nap * 1000,
			philo->container);
		if (ft_isfinished(philo->container))
			break ;
		ft_think(philo);
	}
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
	if (philo->philo_id % 2 == 1)
		usleep(100);
	if (philo->container->hm_philos == 1)
	{
		ft_gnam(philo);
		return (NULL);
	}
	ft_philo_routine(philo);
	return (NULL);
}
