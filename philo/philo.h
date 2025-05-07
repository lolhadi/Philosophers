/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 07:22:31 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/07 13:47:55 by muhabin-         ###   ########.fr       */
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
	long long	start_time;

}	t_philo;

typedef struct s_data
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;// -1 if unlimited
	pthread_mutex_t	*forks; //Array of forks
	pthread_mutex_t	print_mutex; // Mutex for printing
	pthread_mutex_t	death_mutex; // protects the death status
	bool	sim_over; // treu if a philosopher has died
	t_philo	*philos; // Array of philosophers
}	t_data;

//UTILS.c
int		ft_atoi(char *str);
int		error_msg(char *str);

//INIT.c
int		init_data(t_data *data, int argc, char **argv);
