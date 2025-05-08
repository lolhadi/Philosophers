/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhabin- <muhabin-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 07:22:05 by muhabin-          #+#    #+#             */
/*   Updated: 2025/05/08 14:15:43 by muhabin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (init_data(&data, argc, argv) != 0)
		return (1);
	// // Create threads for philosophers
	init_philos(&data);
	// // Create threads for monitors
	if (create_thread(&data) != 0)
	{
		free_resources(&data);
		return (1);
	}

	// // Wait for threads to finish
	// wait_for_threads();
	// // Clean up resources
	// clean_up();
	// // Free allocated memory
	// free_resources();
	return (0);

}
