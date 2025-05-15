/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:22:28 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/14 23:06:30 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_philo *philo)
{
	int	i;
	long long	curr_time;
	int	eating;

	i = -1;
	while (++i < philo->num_philos)
	{
		pthread_mutex_lock(philo->dining_lock);
		eating = philo->eating;
		pthread_mutex_unlock(philo->dining_lock);
		curr_time = get_time();
		if ((curr_time - philo[i].last_meal) >= philo->time_to_die
			&& eating == 0)
		{
			print_status(&philo[i], "died");
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead_flag = 1;
			pthread_mutex_unlock(philo->dead_lock);
			break;
		}
		pthread_mutex_unlock(philo->dining_lock);
	}
}

void	all_eat(t_philo *philo)
{
	int	i;
	int	full;

	full = 0;
	i = -1;
	if (philo->must_eat == -1)
		return ;
	while (++i < philo->num_philos)
	{
		pthread_mutex_lock(philo->dining_lock);
		if (philo[i].meal_count >= philo->must_eat)
			full += 1;
		pthread_mutex_unlock(philo->dining_lock);
	}
	if (full == philo->num_philos)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo->dead_lock);
	}
}
