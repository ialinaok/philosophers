/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:41:20 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/15 20:22:42 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief function creates philosopher threads in a loop, as well as
 * waits for all of the 'philosophers' (threads) to finish
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
		printf("%dth philosopher's thread started.\n", \
		data->philo_arr[i].n_philo + 1);
		i++;
	}
	if (data->n_meals == -1)
		pthread_create(&big_brother, NULL, &unlimited, data);
	else
		pthread_create(&big_brother, NULL, &limited, data);
	pthread_join(big_brother, NULL);
	return (0);
}

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
			pthread_mutex_lock(&(data->be_or_not_lock));
			if (check_if_dead(data, data->philo_arr[i]) == false)
				return (NULL);
			pthread_mutex_unlock(&(data->be_or_not_lock));
			i++;
		}
	}
	return (NULL);
}

bool	check_if_dead(t_data *data, t_philo philo)
{
	long long	time_passed;

	pthread_mutex_lock(&(data->check_meals_lock));
	time_passed = time_now() - philo.last_meal;
	pthread_mutex_unlock(&(data->check_meals_lock));
	if (time_passed >= data->time_to_die && data->be_or_not == true)
	{
		printf("%10lld\t%d\tdied 😵\n", time_now() - data->start, \
		philo.n_philo + 1);
		data->be_or_not = false;
		pthread_mutex_unlock(&(data->be_or_not_lock));
		return (false);
	}
	return (true);
}

void	*limited(void *arg)
{
	int			i;
	t_data		*data;
	long long	time_passed;

	data = (t_data *) arg;
	while (23)
	{
		i = 0;
		if (to_be_or_not_to_be(data) == false)
			return (NULL);
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&(data->be_or_not_lock));
			if (check_if_dead(data, data->philo_arr[i]) == false)
				return (NULL);
			if (check_if_full(data) == false)
				return (NULL);
			pthread_mutex_unlock(&(data->be_or_not_lock));
			i++;
		}
	}
	return (NULL);
}

bool	check_if_full(t_data *data)
{
	if (data->who_finished == data->n_philos \
		&& data->be_or_not == true)
	{
		data->be_or_not = false;
		pthread_mutex_unlock(&(data->be_or_not_lock));
		return (false);
	}
	return (true);
}

int	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_detach(data->philo_arr[i].id);
		printf("%dth philosopher's thread finished execution.\n", \
		data->philo_arr[i].n_philo + 1);
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
