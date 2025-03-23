/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:17:04 by rd-agost          #+#    #+#             */
/*   Updated: 2025/03/23 16:37:13 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//input: ./philo 5 800 200 200 [5] 
//[n of philo, time to die, time to eat, time to nap, number of meals(optional)]

int	main(int ac, char *av[])
{
	t_container container;
	if(ac == 5 || ac == 6)
	{
		ft_parser(&container, av);
		//2 ft_init_data(&container);
		//3 ft_start_dining(&container);
		//4 ft_clean(&container); //trigered if philos arefull or 1 philo dies
	}
	else
	{
		ft_error("Error: wrong input!\n"
			GREEN"The correct input is like :./philo 5 800 200 200 [5]"RESET);
	}
}