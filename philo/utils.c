/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:32:14 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/12 13:27:53 by muhabin-         ###   ########.fr       */
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
	return((int)num);
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;
	int		dead_flag;

	pthread_mutex_lock(philo->dead_lock);
	dead_flag = *philo->dead_flag;
	pthread_mutex_unlock(philo->dead_lock);
	if (dead_flag)
		return ;
	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->print_lock);
	printf("%lld %d %s\n", time, philo->id, status); //check nanti
	pthread_mutex_unlock(philo->print_lock);
}
long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	philo_sleep(long long milisec)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < milisec)
		usleep(500);
	return (0);
}
