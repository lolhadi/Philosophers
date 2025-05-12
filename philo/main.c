/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 07:22:05 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/12 13:31:57 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean_up(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dining_lock);
	if (data->philos)
		free(data->philos);
	data->forks = NULL;
	data->philos = NULL;
}

int	error_msg(char *str)
{
	printf("%s\n", str);
	return (1);
}

static int	valid_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **argv)
{
	int	i;
	int	num;

	i = 0;
	while (argv[++i])
	{
		if (!valid_num(argv[i]))
			return (error_msg("Error: Invalid argument"));
		num = ft_atoi(argv[i]);
		if (num > INT_MAX)
			return (error_msg("Error: Argument too large"));
		if (i == 1 && (num < 1 || num > PHILO_MAX))
			return (error_msg("Error: Number of philosophers must be 1 - 200"));
		else if (i >= 2 && i <= 4 && num < MIN_TIME)
			return (error_msg("Error: Time values must be at least 60ms"));
		else if (i == 5 && num < MIN_MEALS)
			return (error_msg("Error: Number of times to eat must be at least 1"));
	}
	return (0);
}
int main(int argc, char **argv)
{
	t_data	data;

	if (argc !=5 && argc != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	// Check if the arguments are valid integers
	if (check_args(argv))
		return (1);
	// Initialize data(mutexes, timers, etc.)
	printf("before init\n");
	if (init_data(&data, argv) != 0)
		return (1);
	printf("after init\n");
	// // Create threads for monitors
	printf("before create_thread\n");
	feast(&data);
	// // Clean up resources
	clean_up(&data);
	return (0);
}
