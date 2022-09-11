/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:41:20 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/11 17:45:51 by apielasz         ###   ########.fr       */
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
		data->philo_arr[i].last_meal = data->start;
		pthread_create(&(data->philo_arr[i].id), NULL, &routine, &(data->philo_arr[i]));
		printf("%dth philosopher's thread started.\n", data->philo_arr[i].n_philo + 1);
		i++;
	}
	if (data->n_meals == -1) // unlimited
		pthread_create(&big_brother, NULL, &unlimited, data);
	else //limited
		pthread_create(&big_brother, NULL, &limited, data);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philo_arr[i].id, NULL);
		printf("%dth philosopher's thread finished execution.\n", data->philo_arr[i].n_philo + 1);
		i++;
	}
	return (0);
}

void	*unlimited(void *arg) // only check for dying - go through each philosopher one by one
{
	int			i;
	t_data		*data;
	t_philo		*philo;
	long long	time_passed;

	i = 0;
	data = (t_data *) data;
	philo = data->philo_arr;
	while (23)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&(data->done_lock));
			time_passed = time_now() - philo[i].last_meal;
			if (time_passed >= data->time_to_die && data->done == false)
			{
				printf("%lld\t%d\tdied 😵\n", time_now() - data->start, i + 1);
				data->done = true;
				return (NULL);
			}
			pthread_mutex_unlock(&(data->done_lock));
			i++;
		}
	}
}

void	*limited(void *arg)
{
	int			i;
	t_data		*data;
	t_philo		*philo;
	long long	time_passed;

	i = 0;
	data = (t_data *) data;
	philo = data->philo_arr;
	while (23)
	{
		i = 0;
		while (i < data->n_philos)
		{
			pthread_mutex_lock(&(data->done_lock));
			time_passed = time_now() - philo[i].last_meal;
			if (time_passed >= data->time_to_die && data->done == false)
			{
				printf("%lld\t%d\tdied 😵\n", time_now() - data->start, i + 1);
				data->done = true;
				pthread_mutex_unlock(&(data->done_lock));
				return (NULL);
			}
			else if (data->who_finished == data->n_philos)
			{
				data->done = true;
				pthread_mutex_unlock(&(data->done_lock));
				return (NULL);
			}
			pthread_mutex_unlock(&(data->done_lock));
			i++;
		}
	}
}