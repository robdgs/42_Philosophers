/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:13:38 by rd-agost          #+#    #+#             */
/*   Updated: 2025/02/23 21:47:34 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
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
    if (str[i] == '\0')
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
	bool		flag;
	
	i = 0;
	result = 0;
	flag = ft_is_valid(str);
    if (!flag)
    {
        ft_exit_error("Invalid input. Positive numbers only.");
        return -1;
    }
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13) || str[i] == 43)
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result *= 10;
        result += str[i] - '0';
        i++;
    }
    if (result > INT_MAX)
    {
        ft_exit_error("Number too big");
        return -1; 
    }
    return result;
}


void ft_parser(t_container *container, char **av)
{
	//
}