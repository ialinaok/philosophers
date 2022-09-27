/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:41:20 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/27 14:31:17 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief function creates philosopher threads in a loop, as well as
 * the supervising threads. Waits for the supervising thread to finish.
 * 
 * @param data struct with all data
 * @return int 0 on success
 */

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	big_brother;

	i = 0;
	data->start = time_now();
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&(data->check_meals_lock));
		data->philo_arr[i].last_meal = data->start;
		pthread_mutex_unlock(&(data->check_meals_lock));
		pthread_create(&(data->philo_arr[i].id), NULL, &routine, \
		&(data->philo_arr[i]));
		i++;
	}
	if (data->n_meals == -1)
		pthread_create(&big_brother, NULL, &unlimited, data);
	else
		pthread_create(&big_brother, NULL, &limited, data);
	pthread_join(big_brother, NULL);
	return (0);
}

/**
 * @brief function waits for philosopher's threads to finish execution. 
 * Destroys the mutexes and frees the memory that was allocated for forks.
 * 
 * @param data struct with data
 * @return int 
 */

int	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philo_arr[i].id, NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->fork_arr[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->be_or_not_lock));
	pthread_mutex_destroy(&(data->check_meals_lock));
	free(data->fork_arr);
	return (0);
}
