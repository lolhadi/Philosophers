/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:58:35 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/14 22:51:12 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	// pthread_mutex_t	*first;
	// pthread_mutex_t	*second;

	if (philo->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		philo_sleep(philo->time_to_die);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	// if (philo->left_fork < philo->right_fork)
	// {
	// 	first = philo->left_fork;
	// 	second = philo->right_fork;
	// }
	// else
	// {
	// 	first = philo->right_fork;
	// 	second = philo->left_fork;
	// }
	// pthread_mutex_lock(first);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	// pthread_mutex_lock(second);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->dining_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->meal_count++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->dining_lock);
	philo_sleep(philo->time_to_eat);
	// pthread_mutex_unlock(second);
	// pthread_mutex_unlock(first);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	philo_sleep(philo->time_to_sleep);
}
