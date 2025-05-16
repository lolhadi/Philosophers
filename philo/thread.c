/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:53 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/16 10:49:57 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*overseer(void *arg)
{
	t_philo	*philos;
	int		flag;

	philos = (t_philo *)arg;
	while (1)
	{
		is_dead(philos);
		all_eat(philos);
		pthread_mutex_lock(philos->dead_lock);
		flag = *philos->dead_flag;
		pthread_mutex_unlock(philos->dead_lock);
		if (flag == 1)
			break ;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		flag;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		philo_sleep(3);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		flag = *philo->dead_flag;
		pthread_mutex_unlock(philo->dead_lock);
		if (flag == 1)
			break ;
		pthread_mutex_lock(philo->dining_lock);
		if (philo->must_eat != -1 && philo->meal_count >= philo->must_eat)
		{
			pthread_mutex_unlock(philo->dining_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dining_lock);
		eat(philo);
		sleeping(philo);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	feast(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	if (pthread_create(&monitor, NULL, overseer, data->philos) != 0)
		clean_up(data);
	while (++i < data->num_philos)
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			clean_up(data);
	if (pthread_join(monitor, NULL) != 0)
		clean_up(data);
	i = -1;
	while (++i < data->num_philos)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			clean_up(data);
}
