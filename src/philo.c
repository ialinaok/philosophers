/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:37:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/23 16:47:58 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) arg;
	data = philo->data_ptr;
	if (data->n_philos == 1)
		return (one_philo_case(data));
	if (philo->n_philo % 2 == 0)
		usleep(data->time_to_eat * 1000);
	while (to_be_or_not_to_be(data, philo->n_philo) == true)
	{
		if (data->n_meals == 0)
			break ;
		if (to_be_or_not_to_be(data, 12) == true)
			pick_forks(philo);
		if (philo_eat(philo) == false)
			return (NULL);
		if (philo_sleep_think(philo) == false)
			return (NULL);
	}
	return (NULL);
}

void	pick_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data_ptr;
	// if (philo->n_philo % 2 == 0)
	// 	usleep(data->time_to_eat * 1000);
		// usleep(1000);
	// printf("philo %d tries to take right fork\n", philo->n_philo + 1);
	pthread_mutex_lock(philo->right_fork);
	if (to_be_or_not_to_be(data, 15) == true)
		printf("%10lld\t%d\thas taken a right fork ⭕️\n", \
		time_now() - data->start, philo->n_philo + 1);
	// printf("philo %d tries to take left fork\n", philo->n_philo + 1);
	pthread_mutex_lock(philo->left_fork);
	if (to_be_or_not_to_be(data, philo->n_philo) == true)
		printf("%10lld\t%d\thas taken a left fork 🔴\n", \
		time_now() - data->start, philo->n_philo + 1);
}

bool	philo_eat(t_philo *philo)
{
	t_data		*data;
	long long	finish;

	data = philo->data_ptr;
	// printf("philo %d nomnomnonmonm\n", philo->n_philo + 1);
	pthread_mutex_lock(&(data->check_meals_lock));
	philo->last_meal = time_now();
	// printf("philo %d tbontb\n", philo->n_philo + 1);
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->be_or_not == true && data->n_meals != 0)
	{
		printf("%10lld\t%d\tis eating 🍧\n", \
		time_now() - data->start, philo->n_philo + 1);
		philo->times_eaten++;
	}
	if (philo->times_eaten == data->n_meals)
		data->who_finished++;
	pthread_mutex_unlock(&(data->check_meals_lock));
	// printf("philo %d nomnomnom unlock\n", philo->n_philo + 1);
	pthread_mutex_unlock(&(data->be_or_not_lock));
	// printf("philo %d tbontb unlock\n", philo->n_philo + 1);
	finish = philo->last_meal + data->time_to_eat;
	while (time_now() < finish)
	{
		if (to_be_or_not_to_be(data, philo->n_philo) == false)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
		usleep(1000);
	}
	pthread_mutex_unlock(philo->right_fork);
	// printf("philo %d returned right fork %d\n", philo->n_philo + 1, philo->n_philo + 1);
	pthread_mutex_unlock(philo->left_fork);
	// printf("philo %d returned left fork %d\n", philo->n_philo + 1, philo->n_philo + 2);
	return (true);
}

bool	philo_sleep_think(t_philo *philo)
{
	t_data		*data;
	long long	wake;

	data = philo->data_ptr;
	// printf("philo %d tbontb lock\n", philo->n_philo + 1);
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->be_or_not == true)
		printf("%10lld\t%d\tis sleeping 💤\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_unlock(&(data->be_or_not_lock));
	// printf("philo %d tbontb unlock\n", philo->n_philo + 1);
	wake = time_now() + data->time_to_sleep;
	while (time_now() < wake)
	{
		if (to_be_or_not_to_be(data, philo->n_philo) == false)
			return (false);
		usleep(100);
	}
	// printf("philo %d tbontb lock\n", philo->n_philo + 1);
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->be_or_not == true)
		printf("%10lld\t%d\tis thinking 🧠\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_unlock(&(data->be_or_not_lock));
	// printf("philo %d tbontb unlock\n", philo->n_philo + 1);
	return (true);
}

void	*one_philo_case(t_data *data)
{
	pthread_mutex_lock(&(data->be_or_not_lock));
	printf("%10lld\t1\thas taken a right fork ⭕️\n", \
	time_now() - data->start);
	usleep(data->time_to_die * 1000);
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (NULL);
}
