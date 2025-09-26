/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:17:18 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/26 20:50:00 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_error(const char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
	return (true);
}

long	ft_get_time(t_tcode time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_error("Gettimeofday failed");
	else if (time_code == SEC)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISEC)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSEC)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_error("wrong value to gettime");
	return (42);
}

//usleep reale a volte impreciso
//check if the sim is finished to avoid sleep per sempre lol
// - im going to refine last microsec with a spinlock
void	ft_secured_usleep(long usec, t_container *container)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = ft_get_time(MICROSEC);
	elapsed = ft_get_time(MICROSEC) - start;
	while (elapsed < usec)
	{
		if (ft_isfinished(container))
			break ;
		remaining = usec - elapsed;
		if (remaining < 500)
		{
			while (ft_get_time(MICROSEC) - start < usec)
			{
				if (ft_isfinished(container))
					break ;
			}
			break ;
		}
		else if (remaining > 1000)
			usleep(remaining / 3);
		elapsed = ft_get_time(MICROSEC) - start;
	}
}

void	ft_print_status(t_status status, t_philo *philo)
{
	long	t_riman;

	t_riman = ft_get_time(MILLISEC) - philo->container->start_simulation;
	ft_mutex_caller(&philo->container->write_mtx, LOCK);
	if (status == TAKING_FORK && !ft_isfinished(philo->container))
		printf("%-6ld %d has taken a fork\n", t_riman, philo->philo_id);
	else if (status == EATING && !ft_isfinished(philo->container))
		printf("%-6ld %d is eating\n", t_riman, philo->philo_id);
	else if (status == THINKING && !ft_isfinished(philo->container))
		printf("%-6ld %d is thinking\n", t_riman, philo->philo_id);
	else if (status == SLEEPING && !ft_isfinished(philo->container))
		printf("%-6ld %d is sleeping\n", t_riman, philo->philo_id);
	else if (status == DEAD)
		printf("%-6ld %d died\n", t_riman, philo->philo_id);
	ft_mutex_caller(&philo->container->write_mtx, UNLOCK);
}
