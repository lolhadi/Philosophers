/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:32:14 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/15 13:48:10 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	unsigned long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)num);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead_flag && ft_strcmp(status, "died") != 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld %d %s\n", get_time() - philo->start_time, philo->id, status);
	pthread_mutex_unlock(philo->print_lock);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	philo_sleep(long long milisec)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < milisec)
		usleep(500);
	return (0);
}
