/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:47:04 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/15 13:11:50 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->dining_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	while (++i < data-> num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_msg("Fork Mutex failed"));
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->dead_flag = 0;
	data->philos = malloc (sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->forks)
		return (error_msg("Philosopher allocation failed"));
	init_mutexes(data);
	init_philos(data, argv);
	return (0);
}

void	init_philos(t_data *data, char **argv)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].num_philos = data->num_philos;
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].eaten = 0;
		data->philos[i].time_to_die = ft_atoi(argv[2]);
		data->philos[i].time_to_eat = ft_atoi(argv[3]);
		data->philos[i].time_to_sleep = ft_atoi(argv[4]);
		data->philos[i].must_eat = -1;
		if (argv[5])
			data->philos[i].must_eat = ft_atoi(argv[5]);
		data->philos[i].meal_count = -1;
		data->philos[i].start_time = get_time();
		data->philos[i].last_meal = get_time();
		data->philos[i].dead_flag = &data->dead_flag;
		data->philos[i].dead_lock = &data->dead_lock;
		data->philos[i].print_lock = &data->print_lock;
		data->philos[i].dining_lock = &data->dining_lock;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
	}
}
