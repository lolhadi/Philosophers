/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:47:04 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/09 12:28:20 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (error_msg("Error: Forks allocation failed"));
	while (++i < data-> num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_msg("Error: Forks mutex initialization failed"));
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (error_msg("Error: Print mutex initialization failed"));
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (error_msg("Error: Death mutex initialization failed"));
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	if (init_mutexes(data) != 0)
		return (error_msg("Error: Mutex initialization failed"));
	data->sim_over = false;
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return ;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = get_time();
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
	}
}
