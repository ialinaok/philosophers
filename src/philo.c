/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:37:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/26 16:54:19 by apielasz         ###   ########.fr       */
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
	if (philo->n_philo % 2 == 0 && data->time_to_eat < 1000)
		usleep(data->time_to_eat * 1000);
	else if (philo->n_philo % 2 == 0 && data->time_to_eat > 1000)
		usleep(1000);
	while (to_be_or_not_to_be(data) == true)
	{
		if (data->n_meals == 0)
			break ;
		if (to_be_or_not_to_be(data) == true)
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
	pthread_mutex_lock(philo->right_fork);
	if (to_be_or_not_to_be(data) == true)
		printf("%10lld\t%d\thas taken a right fork ⭕️\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_lock(philo->left_fork);
	if (to_be_or_not_to_be(data) == true)
		printf("%10lld\t%d\thas taken a left fork 🔴\n", \
		time_now() - data->start, philo->n_philo + 1);
}

bool	philo_eat(t_philo *philo)
{
	t_data		*data;
	long long	finish;

	data = philo->data_ptr;
	pthread_mutex_lock(&(data->check_meals_lock));
	philo->last_meal = time_now();
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
	pthread_mutex_unlock(&(data->be_or_not_lock));
	finish = philo->last_meal + data->time_to_eat;
	while (time_now() < finish)
	{
		if (to_be_or_not_to_be(data) == false)
			give_back_forks_and_return(philo, false);
		usleep(1000);
	}
	return (give_back_forks_and_return(philo, true));
}

bool	philo_sleep_think(t_philo *philo)
{
	t_data		*data;
	long long	wake;

	data = philo->data_ptr;
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->be_or_not == true)
		printf("%10lld\t%d\tis sleeping 💤\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_unlock(&(data->be_or_not_lock));
	wake = time_now() + data->time_to_sleep;
	while (time_now() < wake)
	{
		if (to_be_or_not_to_be(data) == false)
			return (false);
		usleep(1000);
	}
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->be_or_not == true)
		printf("%10lld\t%d\tis thinking 🧠\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_unlock(&(data->be_or_not_lock));
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
