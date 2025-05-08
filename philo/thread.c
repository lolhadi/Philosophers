/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:53 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/08 14:16:43 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_philos(void *arg)
{
	t_data	*data;
	int	i;
	int 	full_philos;

	data = (t_data *)arg;
	full_philos = 0;// need to check later if the any effect on the program
	while (!data->sim_over)
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
			if (full_philos == data->num_philos)
				sim_ended(data);
			ft_usleep(1000);
		}
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
int	create_thread(t_data *data)
{
	int	i;
	pthread_t	monitor;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
						philo_routine, &data->philos[i]) != 0)
		return(error_msg("Error: Thread creation failed"));

	}
	if (pthread_create(&monitor, NULL, monitor_philos, data) != 0)
		return (error_msg("Error: Monitor thread creation failed"));
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
