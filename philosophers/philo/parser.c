/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:13:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/09/20 17:03:35 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (false);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == 43)
		i++;
	if (str[i] == '\0' || str[i] == 45)
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static int	ft_atoi(char *str)
{
	int		i;
	int		result;
	int		prev_result;
	bool	flag;

	i = 0;
	result = 0;
	flag = ft_is_valid(str);
	if (!flag)
		return (-1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == 43)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev_result = result;
		result *= 10;
		if (result / 10 != prev_result)
			return (-1);
		result += str[i] - '0';
		i++;
	}
	if (result > INT_MAX)
		return (-1);
	return (result);
}

static void	ft_parse_max_meals(t_container *container, char **av)
{
	int	max_meals;

	container->max_meals = -1;
	if (av[5])
	{
		max_meals = ft_atoi(av[5]);
		if (max_meals > 0)
			container->max_meals = max_meals;
	}
}

void	ft_input_parse_n_init(t_container *container, char **av)
{
	int	philo_count;
	int	time_die;
	int	time_eat;
	int	time_nap;

	philo_count = ft_atoi(av[1]);
	time_die = ft_atoi(av[2]);
	time_eat = ft_atoi(av[3]);
	time_nap = ft_atoi(av[4]);
	if (philo_count <= 0 || time_die <= 0 || time_eat <= 0 || time_nap <= 0)
	{
		ft_error("insert valid numbers pls");
		return ;
	}
	if (time_die < 60 || time_eat < 60 || time_nap < 60)
	{
		ft_error("time must be > 60ms");
		return ;
	}
	container->hm_philos = philo_count;
	container->time_to_die = time_die;
	container->time_to_eat = time_eat;
	container->time_to_nap = time_nap;
	ft_parse_max_meals(container, av);
}
