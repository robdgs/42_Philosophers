/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:07:49 by rd-agost          #+#    #+#             */
/*   Updated: 2025/02/23 20:21:12 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> //mutex && threads
#include <sys/time.h> //gettimeofday
#include <limits.h>
#include <stdbool.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

//new types to shorten my lines
typedef pthread_mutex_t type_mutex;
//
typedef struct s_container t_container; //declared here to avoid compiler's rage
//The dining philosophers problem:
/* 
	-various threads(philos) trying to access a common resource(spaghetti)
	Every philo needs two forks to eat from the single spaghetti plate:
	we have collision if all the philos eat simultaneously
*/

//what is a fork? a fork is simply a mutex: I'll have an array of mutex
typedef struct	s_fork
{
	type_mutex	fork;
	int			fork_id;
}				t_fork;

//what is a philo? every philo is a struct: I'll have an array of struct
typedef struct	s_philo
{
	int			philo_id;
	long		hm_meals; //meals counter
	bool		is_full;
	long		lmeal_time; //time passed from last meal
	t_fork		r_fork;
	t_fork		l_fork;
	pthread_t	thread_id; //philo_id, philo === a thread
	t_container *container;
}				t_philo;
//plus I need a struct where to put the input line data, a container
struct s_container
{
	long	hm_philos; //how many philos
	long	time_to_die;
	long	time_to_eat;
	long	time_to_nap;
	long	max_meals; //limit of how many meals each philo can have || FLAG
	long	start_simulation; //time when the sim starts
	bool	end_sim; // triggered when a philo dies or all philos are full
	t_philo	*philos; //ptr to array of philos
	t_fork	*forks; //ptr to array of forks
};			

//utils.c
void	ft_exit_error(const char *error);

//philo_parser.c
void ft_parser(t_container *container, char **av);
