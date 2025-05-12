/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:22:28 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/12 15:45:33 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_philo *philo)
{
	int	i;
	long long	curr_time;

	curr_time = get_time();
	i = -1;
	while (++i < philo->data->num_philos)
	{
		pthread_mutex_lock(&philo->data->dining_lock);
		if ((curr_time - philo[i].last_meal) >= philo->data->time_to_die)
		{
			print_status(&philo[i], "died");
			pthread_mutex_unlock(&philo->data->dining_lock);
			pthread_mutex_lock(&philo->data->dead_lock);
			philo->data->dead_flag = 1;
			pthread_mutex_unlock(&philo->data->dead_lock);
		}
		pthread_mutex_unlock(&philo->data->dining_lock);
	}
}

// int	all_eat(t_data *data)
// {
// 	int	i;
// 	int	all_full;

// 	if (data->must_eat == -1)
// 		return 1;
// 	all_full = 1;
// 	i = -1;
// 	while (++i < data->num_philos)
// 	{
// 		pthread_mutex_lock(&data->dining_lock);
// 		if (data->philos[i].eaten < data->must_eat)
// 			all_full = 0;
// 		pthread_mutex_unlock(&data->dining_lock);
// 		if (!all_full)
// 			break ;
// 	}
// 	if (all_full)
// 	{
// 		pthread_mutex_lock(&data->dead_lock);
// 		data->dead_flag = 1;
// 		pthread_mutex_unlock(&data->dead_lock);
// 	}
// 	return (all_full);
// }
void	all_eat(t_data *data)
{
	int	i;
	int	full;

	full = 0;
	i = -1;
	if (data->must_eat == -1)
		return ;
	while (++i < data->num_philos)
		if (data->philos[i].meal_count == data->must_eat)
			full += 1;
	if (full == data->num_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
	}
}
