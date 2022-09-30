/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:30:20 by ialinaok          #+#    #+#             */
/*   Updated: 2022/09/27 14:31:07 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief function takes a data struct and accesses the status variable
 * by unlocking and locking the guarding mutex. Copies the status to a 
 * different to prevent data races.
 * 
 * @param data data struct with data
 * @return true if simulation is meant to continue
 * @return false if simulation is meant to continue
 */

bool	to_be_or_not_to_be(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&(data->be_or_not_lock));
	status = data->be_or_not;
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (status);
}

/**
 * @brief function that is called in the scenario when philosophers
 * are not given the minimum amount of meals they should have.
 * Checks for the status signal of all philosophers.
 * 
 * @param arg (t_data *) data struct with all the data
 * @return void* returns NULL pointer
 */

void	*unlimited(void *arg)
{
	int			i;
	t_data		*data;

	data = (t_data *) arg;
	while (23)
	{
		i = 0;
		if (to_be_or_not_to_be(data) == false)
			return (NULL);
		while (i < data->n_philos)
		{
			if (check_if_dead(data, data->philo_arr[i]) == false)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

/**
 * @brief function that is called in the scenario when philosophers
 * are given the minimum amount of meals they should have.
 * Checks for the status signal of all philosophers.
 * 
 * @param arg (t_data *) data struct with all the data
 * @return void* returns NULL pointer
 */

void	*limited(void *arg)
{
	int			i;
	t_data		*data;

	data = (t_data *) arg;
	while (23)
	{
		i = 0;
		if (to_be_or_not_to_be(data) == false)
			return (NULL);
		while (i < data->n_philos)
		{
			if (check_if_dead(data, data->philo_arr[i]) == false)
				return (NULL);
			if (check_if_full(data) == false)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

/**
 * @brief function calculates if a given philosopher has died, prints the
 * message if yes and changes the status variable to false.
 * 
 * @param data struct with all data
 * @param philo philo struct
 * @return true if simulation is meant to continue
 * @return false if simulation is meant to stop
 */

bool	check_if_dead(t_data *data, t_philo philo)
{
	long long	time_passed;

	pthread_mutex_lock(&(data->check_meals_lock));
	time_passed = time_now() - philo.last_meal;
	pthread_mutex_unlock(&(data->check_meals_lock));
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (time_passed >= data->time_to_die && data->be_or_not == true)
	{
		data->be_or_not = false;
		printf("%10lld\t%d\tdied 😵\n", time_now() - data->start, \
		philo.n_philo + 1);
		pthread_mutex_unlock(&(data->be_or_not_lock));
		return (false);
	}
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (true);
}

/**
 * @brief function checks if the philosophers ate the minimum required
 * amount of meals.
 * 
 * @param data stuct with data
 * @return true if simulation is meant to continue
 * @return false if simulation is meant to stop
 */

bool	check_if_full(t_data *data)
{
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->n_meals == 0)
	{
		data->be_or_not = false;
		pthread_mutex_unlock(&(data->be_or_not_lock));
		return (false);
	}
	if (data->who_finished == data->n_philos \
		&& data->be_or_not == true)
	{
		data->be_or_not = false;
		pthread_mutex_unlock(&(data->be_or_not_lock));
		return (false);
	}
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (true);
}
