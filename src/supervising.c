/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervising.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:30:20 by ialinaok          #+#    #+#             */
/*   Updated: 2022/09/23 15:25:17 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	to_be_or_not_to_be(t_data *data, int philo)
{
	bool	status;
	(void)philo;
	// printf("philo %d tbontb lock on\n", philo);
	pthread_mutex_lock(&(data->be_or_not_lock));
	status = data->be_or_not;
	pthread_mutex_unlock(&(data->be_or_not_lock));
	// printf("philo %d tbontb lock off\n", philo);
	return (status);
}

void	*unlimited(void *arg)
{
	int			i;
	t_data		*data;

	data = (t_data *) arg;
	while (23)
	{
		i = 0;
		if (to_be_or_not_to_be(data, 23) == false)
			return (NULL);
		while (i < data->n_philos)
		{
			// printf("philo %d tbontb lock on\n", 42);
			// pthread_mutex_lock(&(data->be_or_not_lock));
			if (check_if_dead(data, data->philo_arr[i]) == false)
				return (NULL);
			// pthread_mutex_unlock(&(data->be_or_not_lock));
			// printf("philo %d tbontb lock off\n", 42);
			i++;
		}
	}
	return (NULL);
}

void	*limited(void *arg)
{
	int			i;
	t_data		*data;

	data = (t_data *) arg;
	while (23)
	{
		// printf("🌸\n");
		i = 0;
		if (to_be_or_not_to_be(data, 23) == false)
			return (NULL);
		while (i < data->n_philos)
		{
			// printf("philo %d tbontb lock on\n", 42);
			if (check_if_dead(data, data->philo_arr[i]) == false)
				return (NULL);
			if (check_if_full(data) == false)
				return (NULL);
			// pthread_mutex_unlock(&(data->be_or_not_lock));
			// printf("philo %d tbontb lock off\n", 42);
			i++;
		}
	}
	return (NULL);
}

bool	check_if_dead(t_data *data, t_philo philo)
{
	long long	time_passed;
	// printf("check meals lock on\n");
	pthread_mutex_lock(&(data->check_meals_lock));
	time_passed = time_now() - philo.last_meal;
	pthread_mutex_unlock(&(data->check_meals_lock));
	// printf("check meals lock off\n");
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (time_passed >= data->time_to_die && data->be_or_not == true)
	{
		data->be_or_not = false;
		printf("%10lld\t%d\tdied 😵\n", time_now() - data->start, \
		philo.n_philo + 1);
		pthread_mutex_unlock(&(data->be_or_not_lock));
		// printf("philo 42 tbontb lock off\n");
		return (false);
	}
	// printf("nobody dies 😉\n");
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (true);
}

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
		// printf("philo 42 tbontb lock off\n");
		return (false);
	}
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (true);
}
