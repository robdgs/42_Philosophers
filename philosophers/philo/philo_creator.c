/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:35:45 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/24 16:34:25 by rd-agost         ###   ########.fr       */
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

void	ft_philos_init(t_container *container)
{
	container->end_sim = false;
	container->philos = ft_malloc(container->hm_philos);
}