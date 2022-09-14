/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:41:20 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/14 18:24:19 by apielasz         ###   ########.fr       */
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
		data->philo_arr[i]->last_meal = data->start;
		pthread_create(&(data->philo_arr[i]->id), NULL, &routine, data->philo_arr[i]);
		printf("%dth philosopher's thread started.\n", data->philo_arr[i]->n_philo + 1);
		i++;
	}
	if (data->n_meals == -1) // unlimited
		pthread_create(&big_brother, NULL, &unlimited, data);
	else //limited
		pthread_create(&big_brother, NULL, &limited, data);
	return (0);
}

void	*unlimited(void *arg) // only check for dying - go through each philosopher one by one
{
	int			i;
	t_data		*data;
	t_philo		*philo;
	long long	time_passed;

	i = 0;
	data = (t_data *) arg;
	philo = *data->philo_arr;
	while (23)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&(data->be_or_not_lock));
			time_passed = time_now() - philo[i].last_meal;
			if (time_passed >= data->time_to_die && data->be_or_not == true)
			{
				printf("%10lld\t%d\tdied 😵\n", time_now() - data->start, i + 1);
				data->be_or_not = false;
				return (NULL);
			}
			pthread_mutex_unlock(&(data->be_or_not_lock));
			i++;
		}
	}
	return (NULL);
}

void	*limited(void *arg)
{
	int			i;
	t_data		*data;
	t_philo		*philo;
	long long	time_passed;

	i = 0;
	data = (t_data *) arg;
	philo = *data->philo_arr;
	while (23)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&(data->be_or_not_lock));
			time_passed = time_now() - philo[i].last_meal;
			if (time_passed >= data->time_to_die && data->be_or_not == true)
			{
				printf("%10lld\t%d\tdied 😵\n", time_now() - data->start, i + 1);
				data->be_or_not = false;
				pthread_mutex_unlock(&(data->be_or_not_lock));
				return (NULL);
			}
			else if (data->who_finished == data->n_philos)
			{
				data->be_or_not = false;
				pthread_mutex_unlock(&(data->be_or_not_lock));
				return (NULL);
			}
			pthread_mutex_unlock(&(data->be_or_not_lock));
			i++;
		}
	}
	return (NULL);
}

int	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philo_arr[i]->id, NULL);
		printf("%dth philosopher's thread finished execution.\n", data->philo_arr[i]->n_philo + 1);
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
	i = 0;
	while (i < data->n_philos)
		free(&(data->philo_arr[i++]));
	free(data->philo_arr);
	free(data->fork_arr);
	return (0);
}
