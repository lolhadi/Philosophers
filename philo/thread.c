/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:53 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/13 15:33:31 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	join_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			data->dead_flag = 1;
			return (1);
		}
	}
	return (0);
}
int	create_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if(pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
		{
			data->dead_flag = 1;
			return (1);
		}
	}
	return (0);
}

void	*overseer(void *arg)
{
	t_data *data;
	int	flag;

	data = (t_data *)arg;
	while (1)
	{
		is_dead(data->philos);
		pthread_mutex_lock(&data->dead_lock);
		flag = data->dead_flag;
		pthread_mutex_unlock(&data->dead_lock);
		if (flag == 1)
			break ;
		all_eat(data);
		usleep(1000);
	}
	return (NULL);
}
void *philo_routine(void *arg)
{
	t_philo	*philo;
	int		flag;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		philo_sleep(3);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		flag = philo->data->dead_flag;
		pthread_mutex_unlock(philo->dead_lock);
		if (flag == 1)
			break ;
		pthread_mutex_lock(&philo->data->dining_lock);
		if (philo->data->must_eat != -1 && philo->meal_count >= philo->data->must_eat)
		{
			pthread_mutex_unlock(&philo->data->dining_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dining_lock);
		eat(philo);
		sleeping(philo);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
void	feast(t_data *data)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &overseer, data) != 0)
		clean_up(data);
	if (create_philo(data) != 0)
	{
		pthread_join(monitor, NULL);
		return (clean_up(data));
	}
	if (pthread_join(monitor, NULL) != 0)
		data->dead_flag = 1;
	join_philo(data);
	// clean_up(data);
}
