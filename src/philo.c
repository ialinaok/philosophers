/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:37:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/14 21:12:50 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine_basic(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->n_philo % 2 == 0)
		usleep(10 * 1000);
	printf("philosopher [%d] starts eating 😋\n", philo->n_philo);
	printf("philosopher [%d] starts eating 😋\n", philo->n_philo + 1);
	usleep(philo->data_ptr->time_to_eat);
	printf("philosopher [%d] finished eating 🤰\n", philo->n_philo);
	printf("philosopher [%d] finished eating 🤰\n", philo->n_philo + 1);
	return (NULL);
}

bool	to_be_or_not_to_be(t_data *data) // is true for continuing simulation, false for breaking it
{
	bool	status;

	pthread_mutex_lock(&(data->be_or_not_lock));
	status = data->be_or_not;
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (status);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *) arg;
	data = philo->data_ptr;
	if (data->n_philos == 1)
		return (one_philo_case(data));
	if (philo->n_philo % 2 == 0)
		usleep(70);
	while (to_be_or_not_to_be(data) == true)
	{
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
	printf("%10lld\t%d\thas taken a right fork ⭕️\n", \
	time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_lock(philo->left_fork);
	printf("%10lld\t%d\thas taken a left fork 🔴\n", \
	time_now() - data->start, philo->n_philo + 1);
}

bool	philo_eat(t_philo *philo)
{
	t_data		*data;
	long long	finish;

	data = philo->data_ptr;
	pthread_mutex_lock(&(data->check_meals_lock));
	philo->last_meal = time_now(); // not sure about this one as well
	pthread_mutex_unlock(&(data->check_meals_lock));
	pthread_mutex_lock(&(data->be_or_not_lock));
	if (data->be_or_not == true)
		printf("%10lld\t%d\tis eating 🍧\n", \
		time_now() - data->start, philo->n_philo + 1);
	philo->times_eaten++;
	pthread_mutex_unlock(&(data->be_or_not_lock));
	finish = time_now() + data->time_to_eat; //not sure where to put it...
	while (time_now() < finish)
	{
		if (to_be_or_not_to_be(data) == false)
			return (false);
		usleep(1000);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (true);
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
		usleep(100);
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
	printf("%10lld\t1\tdied 😵\n", time_now() - data->start);
	pthread_mutex_unlock(&(data->be_or_not_lock));
	return (NULL);
}