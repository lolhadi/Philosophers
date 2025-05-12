/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:58:35 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/12 13:30:52 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	takes_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	print_status(philo, "has taken a fork");
// 	if (philo->data->num_philos == 1)
// 	{
// 		ft_usleep(philo->data->time_to_die + 10);
// 		pthread_mutex_unlock(philo->left_fork);
// 		return ;
// 	}
// 	pthread_mutex_lock(philo->right_fork);
// 	print_status(philo, "has taken a fork");
// }

// void	releasefork(t_philo *philo)
// {
// 	pthread_mutex_unlock(philo->right_fork);
// 	pthread_mutex_unlock(philo->left_fork);
// }

void	eat(t_philo *philo)
{
	if (philo->data->num_philos == 1)
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->dining_lock);
	philo->last_meal = get_time();
	philo->eating = 1;
	philo->meal_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->dining_lock);
	print_status(philo, "is eating");
	philo_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	philo_sleep(philo->data->time_to_sleep);
}

