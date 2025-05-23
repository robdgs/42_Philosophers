/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:07:49 by rd-agost          #+#    #+#             */
/*   Updated: 2025/04/16 17:22:03 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h> //mutex && threads
# include <sys/time.h> //gettimeofday
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

//operation codes for cpu (mutex && threads) (enum x indicizzazione)
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	JOIN,
	CREATE,
	DESTROY,
	DETACH
}	t_opcode;

typedef enum e_tcode
{
	SEC,
	MILLISEC,
	MICROSEC
}	t_tcode;

typedef enum e_status
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
	TAKING_FFORK,
	TAKING_SFORK,
}	t_status;

//new types to shorten my lines
typedef pthread_mutex_t		t_mutex;
//
typedef struct s_container	t_container;//declared here to avoid compiler's rage
//The dining philosophers problem:
/* 
	-various threads(philos) trying to access a common resource(spaghetti)
	Every philo needs two forks to eat from the single spaghetti plate:
	we have collision if all the philos eat simultaneously
*/
//what is a fork? a fork is simply a mutex: I'll have an array of mutex
/* Per realizzare l'esclusione mutua(MUT EX) si assegna a un oggetto o porzione 
di programma (sezione critica) un elemento che va sempre controllato prima 
che un altro processo o thread possa eseguire istruzioni sull'oggetto stesso. 
Se un processo o thread sta già accedendo all'oggetto, tutti gli altri devono 
aspettare che il primo finisca. Gli oggetti mutex utilizzati per coordinare 
processi diversi devono essere di per sé accessibili a tutti i processi 
coinvolti, il che implica necessariamente l'uso di memoria condivisa, 
oppure gestita direttamente dal sistema operativo. */
typedef struct s_fork
{
	t_mutex		fork;
	int			fork_id;
}				t_fork;

//what is a philo? every philo is a struct: I'll have an array of struct
typedef struct s_philo
{
	int			philo_id; //NOT THE POSITION IN THE ARRAY
	int			hm_meals; //meals counter
	bool		is_full;
	long		lmeal_time; //time passed from last meal
	t_fork		f_fork;
	t_fork		s_fork;
	t_mutex		philo_mutex;
	pthread_t	thread_id; //philo_id, philo === a thread
	t_container	*container;
}				t_philo;
//plus I need a struct where to put the input line data, a container
struct s_container
{
	long	hm_philos; //how many philos
	long	time_to_die;
	long	time_to_eat;
	long	time_to_nap;
	long	max_meals; //limit of how many meals each philo can have || FLAG
	bool	sync;
	t_mutex	container_mtx; //avoid races while READING
	t_mutex	write_mtx; //avoid races while WRITING
	long	start_simulation; //time when the sim starts
	bool	end_sim; // triggered when a philo dies or all philos are full
	t_philo	*philos; //ptr to array of philos
	t_fork	*forks; //ptr to array of forks
};			

//utils
bool	ft_error(const char *error);
long	ft_get_time(t_tcode time_code);
void	ft_secured_usleep(long usec, t_container *container);
void	ft_print_status(t_status status, t_philo *philo);
//guardians
void	*ft_malloc(size_t bytes);
void	ft_mutex_caller(t_mutex *mutex, t_opcode opcode);
void	ft_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
//parse
void	ft_input_parse_n_init(t_container *container, char **av);
//init
void	ft_global_init(t_container *container);
//getters -> syncro
bool	ft_get_bool(t_mutex *mutex, bool *val);
long	ft_get_long(t_mutex *mutex, long *val);
//setters -> syncro
void	ft_set_bool(t_mutex *mutex, bool *dest, bool val);
void	ft_set_long(t_mutex *mutex, long *dest, long val);
//synchro and monitor
void	ft_synchronizer(t_container	*container);
bool	ft_isfinished(t_container *container);
//gnam
void	ft_start(t_container *container);
void	ft_gnam(t_philo *philo);

#endif