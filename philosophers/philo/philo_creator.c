/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:35:45 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/25 16:36:36 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//todo:
// set: bool end_sim
//		t_philo	*philos
//philo:
/* 	
	int			philo_id;
	long		hm_meals; //meals counter
	bool		is_full;
	long		lmeal_time; //time passed from last meal
	t_fork		r_fork;
	t_fork		l_fork;
	pthread_t	thread_id; //philo_id, philo === a thread
	t_container *container; */
//p -> position in container
static void ft_give_forks(t_philo *philo, t_fork *forks, int p)
{
	
}

static void	ft_philo_init(t_container *container)
{
	int	i;
	
	i = -1;
	while(++i < container->hm_philos)
	{
		container->philos->container = container;
		container->philos->philo_id = i;
		container->philos->is_full = false;
		container->philos->hm_meals = 0;
		ft_give_forks(container->philos, container->forks, i);
		
	}
	
}
	
void	ft_global_init(t_container *container)
{
	int	i;
	
	i = -1;
	container->end_sim = false;
	container->philos = ft_malloc(sizeof(t_philo) * container->hm_philos);
	container->forks = ft_malloc(sizeof(t_fork) * container->hm_philos);
	while(++i < container->hm_philos)
	{
		ft_mutex_caller(&container->forks[i],INIT);
		container->forks[i].fork_id = i;
	}
	ft_philo_init(container); //doing
}