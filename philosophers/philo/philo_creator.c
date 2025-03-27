/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:35:45 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/27 18:15:22 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//todo:
// set: bool end_sim
//		t_philo	*philos
//philo:
/* 	
	int			philo_id;
	int		hm_meals; //meals counter
	bool		is_full;
	int		lmeal_time; //time passed from last meal
	t_fork		r_fork;
	t_fork		l_fork;
	pthread_t	thread_id; //philo_id, philo === a thread
	t_container *container; */
//p -> position in container == THE i value of philo init, i know how 
//	many philos are there
/* 
right fork -> philo_id - 1 == position in the array
la frchetta sinistra dell'ultimo filosofo e' la forchetta zero, quindi
left fork -> (philo_id + 1) % quanti filosofi ossia p
ESEMPIO (4 + 1) % 5 = 0 La forchetta left dell'ultimo philo e' la 0
CIRCULAR OBJECT ---->> MODULE OPERATOR %
*/
//attenzione possibili deadlock qui
static void ft_give_forks(t_philo *philo, t_fork *forks, int p)
{
	
	if(philo->philo_id % 2 == 0)
	{
		philo->f_fork = forks[p];
		philo->s_fork = forks[(p + 1) % philo->container->hm_philos];
	}
	else
	{
		philo->f_fork = forks[(p + 1) % philo->container->hm_philos];
		philo->s_fork = forks[p];
	}
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
	ft_mutex_caller(&container->container_mtx, INIT);
	container->forks = ft_malloc(sizeof(t_fork) * container->hm_philos);
	while(++i < container->hm_philos)
	{
		ft_mutex_caller(&container->forks[i].fork,INIT);
		container->forks[i].fork_id = i;
	}
	ft_philo_init(container);
}

