/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:53 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/09 14:11:15 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->print_mutex);
}
void set_sim_end(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->sim_over = true;
	pthread_mutex_unlock(&data->death_mutex);
}

void *monitor_philos(void *arg)
{
	t_data	*data;
	int	i;
	int 	full_philos;

	data = (t_data *)arg;
	full_philos = 0;// need to check later if the any effect on the program
	printf("monitor thread\n");
	while (!sim_ended(data))
	{
		i = -1;
		full_philos = 0;
		while (++i < data->num_philos)
		{
			if (check_starve(&data->philos[i]))
				return (NULL);
			if (data->must_eat != -1
				&& data->philos[i].eaten >= data->must_eat)
				full_philos++;
		}
		if (full_philos == data->num_philos)
		{
			printf("inhere now \n");
				set_sim_end(data);
				return (NULL);
		}
		ft_usleep(1000);
	}
	return (NULL);
}
void *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!sim_ended(philo->data))
	{
		think(philo);
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
void	create_thread(t_data *data)
{
	int	i;
	pthread_t	monitor;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
						philo_routine, &data->philos[i]) != 0)
		{
			printf("Error: Thread creation failed\n");
			sim_ended(data);
			return ;
		}
	}
		printf("before monitor thread\n");
	if (pthread_create(&monitor, NULL, monitor_philos, data) != 0)
		{
			printf("Error: Monitor thread creation failed\n");
			sim_ended(data);
			return ;
		}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
}
