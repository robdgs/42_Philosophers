/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:35:45 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/21 18:26:11 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_give_forks(t_philo *philo, t_fork *forks, int p)
{
	int	left_fork;
	int	right_fork;

	left_fork = p;
	right_fork = (p + 1) % philo->container->hm_philos;
	if (left_fork < right_fork)
	{
		philo->f_fork = &forks[left_fork];
		philo->s_fork = &forks[right_fork];
	}
	else
	{
		philo->f_fork = &forks[right_fork];
		philo->s_fork = &forks[left_fork];
	}
	if (philo->container->hm_philos % 2 == 1
		&& p == philo->container->hm_philos - 1)
	{
		philo->f_fork = &forks[right_fork];
		philo->s_fork = &forks[left_fork];
	}
}

static void	ft_philo_init(t_container *container)
{
	int	i;

	i = -1;
	while (++i < container->hm_philos)
	{
		container->philos[i].container = container;
		container->philos[i].philo_id = i + 1;
		container->philos[i].is_full = false;
		container->philos[i].hm_meals = 0;
		container->philos[i].lmeal_time = 0;
		ft_mutex_caller(&container->philos[i].philo_mutex, INIT);
		ft_give_forks(&container->philos[i], container->forks, i);
	}
	container->sync = false;
}

void	ft_global_init(t_container *container)
{
	int	i;

	i = -1;
	container->end_sim = false;
	container->philos = ft_malloc(sizeof(t_philo) * container->hm_philos);
	ft_mutex_caller(&container->container_mtx, INIT);
	ft_mutex_caller(&container->write_mtx, INIT);
	container->forks = ft_malloc(sizeof(t_fork) * container->hm_philos);
	while (++i < container->hm_philos)
	{
		ft_mutex_caller(&container->forks[i].fork, INIT);
		container->forks[i].fork_id = i;
	}
	ft_philo_init(container);
}
