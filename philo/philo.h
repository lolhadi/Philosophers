/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 07:22:31 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/09 12:56:03 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>


# define PHILO_MAX 200
# define MIN_TIME 60
# define MIN_MEALS 1

typedef struct s_philo
{
	int		id;
	int		eat_count;
	int		eaten;
	long long	last_meal;
	pthread_t	thread; // Thread ID
	struct s_data	*data; // Pointer to the data structure
	pthread_mutex_t	*left_fork; // Pointer to the left fork
	pthread_mutex_t	*right_fork; // Pointer to the right fork
}	t_philo;

typedef struct s_data
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;// -1 if unlimited
	long long	start_time;
	pthread_mutex_t	*forks; //Array of forks
	pthread_mutex_t	print_mutex; // Mutex for printing
	pthread_mutex_t	death_mutex; // protects the death status
	bool	sim_over; // treu if a philosopher has died
	t_philo	*philos; // Array of philosophers
}	t_data;

//UTILS.c
int		ft_atoi(char *str);
int		error_msg(char *str);
int		sim_ended(t_data *data);
void		print_status(t_philo *philo, char *status);
long long	get_time(void);
void		ft_usleep(long long time);

//INIT.c
int			init_data(t_data *data, int argc, char **argv);
int			init_mutexes(t_data *data);
void		init_philos(t_data *data);


//THREAD.c
void		*philo_routine(void *arg);
void		*monitor_philos(void *arg);
void			create_thread(t_data *data);
int			check_starve(t_philo *philo);
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		philo_sleep(t_philo *philo);

