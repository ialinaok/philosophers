/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:53:53 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/27 14:47:07 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief function initiates the data struct, creates forks, initializes mutexes
 * and initializes philosophers array
 * 
 * @param data struct to be initialized
 * @param argc arg from main function
 * @param argv arg from main function
 * @return int return -1 if allocation fails
 */

int	init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	load_struct(data, argc, argv);
	pthread_mutex_init(&(data->be_or_not_lock), NULL);
	pthread_mutex_init(&(data->check_meals_lock), NULL);
	data->fork_arr = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->fork_arr)
		return (-1);
	i = 0;
	while (i < data->n_philos)
	{
		data->philo_arr[i].n_philo = i;
		data->philo_arr[i].data_ptr = data;
		data->philo_arr[i].times_eaten = 0;
		if (pthread_mutex_init(&(data->fork_arr[i]), NULL) != 0)
			return (-1);
		data->philo_arr[i].right_fork = &(data->fork_arr[i]);
		if (i == data->n_philos - 1)
			data->philo_arr[i].left_fork = &(data->fork_arr[0]);
		else
			data->philo_arr[i].left_fork = &(data->fork_arr[i + 1]);
		i++;
	}
	return (0);
}

/**
 * @brief function takes args given to main function and initilizes
 * data stuct with correct values + other values
 * 
 * @param data struct to be initialized
 * @param argc arg from main function
 * @param argv arg from main function
 */

void	load_struct(t_data *data, int argc, char **argv)
{
	data->be_or_not = true;
	data->n_philos = (int) ft_atoli(argv[1]);
	data->time_to_die = (int) ft_atoli(argv[2]);
	data->time_to_eat = (int) ft_atoli(argv[3]);
	if (data->time_to_eat == 0)
		data->time_to_eat = 10;
	data->time_to_sleep = (int) ft_atoli(argv[4]);
	data->sleep_or_not = true;
	if (data->time_to_sleep == 0)
	{
		data->time_to_sleep = 10;
		data->sleep_or_not = false;
	}
	if (argc == 6)
		data->n_meals = (int) ft_atoli(argv[5]);
	else
		data->n_meals = -1;
	data->who_finished = 0;
}
