/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 07:22:31 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/12 13:34:29 by muhabin-         ###   ########.fr       */
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
	int		eating;
	int		meal_count;
	int		eaten;
	int		*dead_flag;
	long long	last_meal;
	long long	start_time;
	pthread_t	thread;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dining_lock;
	pthread_mutex_t	*left_fork; // Pointer to the left fork
	pthread_mutex_t	*right_fork; // Pointer to the right fork
	struct s_data	*data; // Pointer to the data structure
}	t_philo;

typedef struct s_data
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;// -1 if unlimited
	int		dead_flag;

	pthread_mutex_t	*forks; //Array of forks
	pthread_mutex_t	dead_lock; // Mutex for printing
	pthread_mutex_t	dining_lock;
	pthread_mutex_t	print_lock;
	// bool	sim_over; // treu if a philosopher has died
	t_philo	*philos; // Array of philosophers
}	t_data;

//UTILS.c
int		ft_atoi(char *str);
int		error_msg(char *str);
void		print_status(t_philo *philo, char *status);
long long	get_time(void);
int		philo_sleep(long long milisec);
int		is_dead(t_philo *philo);
int		all_eat(t_data *data);
void clean_up(t_data *data);

//INIT.c
int			init_data(t_data *data, char **argv);
int			init_mutexes(t_data *data);
void		init_philos(t_data *data);


//THREAD.c
void		*philo_routine(void *arg);
void		*overseer(void *arg);
void		feast(t_data *data);
// int			check_starve(t_philo *philo);
void		eat(t_philo *philo);
// void		think(t_philo *philo);
void		sleeping(t_philo *philo);

