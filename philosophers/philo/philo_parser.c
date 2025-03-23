/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:13:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/23 17:49:06 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
+ 43
- 45
- numbers
- minore di int max
- timestamp > 60 ms
*/
bool	ft_is_valid(char *str)
{
    int i;

	i = 0;
    if (str == NULL || str[0] == '\0')
		return false;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == 43)
        i++;
    if (str[i] == '\0' || str[i] == 45 )
		return false;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9') 
            return false;
        i++;
    }
    return true;
}

static long	ft_atol(char *str)
{
	int			i;
	long int	result;
    long int    prev_result;
	bool		flag;
	
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
    return result;
}


void ft_input_parse_n_init(t_container *container, char **av)
{
    long philo_count, time_die, time_eat, time_sleep, max_meals;

    philo_count = ft_atol(av[1]);
    time_die = ft_atol(av[2]);
    time_eat = ft_atol(av[3]);
    time_sleep = ft_atol(av[4]);

    if (philo_count <= 0 || time_die <= 0 || time_eat <= 0 || time_sleep <= 0)
    {
        ft_error("insert valid numbers pls");
        return;
    }

    if (time_die < 6e4 || time_eat < 6e4 || time_sleep < 6e4)
    {
        ft_error("time must be > 60ms");
        return;
    }
    container->hm_philos = philo_count;
    container->time_to_die = time_die * 1e3;
    container->time_to_eat = time_eat * 1e3;
    container->time_to_nap = time_sleep * 1e3;
    if (av[5])
    {
        max_meals = ft_atol(av[5]);
        if (max_meals > 0)
            container->max_meals = max_meals;
        else
            ft_error("max_meals must be a positive number");
    }
    else
        container->max_meals = -1;
}