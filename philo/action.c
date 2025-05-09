/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:58:35 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/09 12:49:51 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	takes_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die + 10);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	releasefork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philo *philo)
{
	takes_fork(philo);
	pthread_mutex_lock(&philo->data->print_mutex);
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->eaten++;
	pthread_mutex_unlock(&philo->data->print_mutex);
	ft_usleep(philo->data->time_to_eat);
	releasefork(philo);
}
void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

int	check_starve(t_philo *philo)
{
	long	curr_time;

	pthread_mutex_lock(&philo->data->death_mutex);
	curr_time = get_time();
	if (curr_time - philo->last_meal > philo->data->time_to_die
		&& !philo->data->sim_over)
	{
		printf("before death\n");
		print_status(philo, "died");
		philo->data->sim_over = true;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}
