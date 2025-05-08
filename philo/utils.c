/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:32:14 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/08 14:14:21 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *str)
{
	printf("%s\n", str);
	return (1);
}

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

bool	sim_ended(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->death_mutex);
	ret = data->sim_over;
	pthread_mutex_unlock(&data->death_mutex);
	return (ret);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!sim_ended(philo->data))
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time,
			philo->id, status); // later try to id + 1
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void ft_usleep(long long time)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(100);
}
