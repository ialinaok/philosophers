/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:37:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/12 21:03:12 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) arg;
// 	if (philo->n_philo % 2 == 0)
// 		usleep(70);
// 	printf("philosopher [%d] starts eating 😋\n", philo->n_philo + 1);
// 	usleep(philo->data_ptr->time_to_eat);
// 	printf("philosopher [%d] finished eating 🤰\n", philo->n_philo + 1);
// 	return (NULL);
// }

bool	check_done(t_data *data)
{
	bool	status;

	pthread_mutex_lock(&(data->done_lock));
	status = data->done;
	pthread_mutex_lock(&(data->done_lock));
	return (status);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *) arg;
	data = philo->data_ptr;
	if (philo->n_philo % 2 == 0)
		usleep(70);
	while (check_done(data) == false)
	{
		pick_forks(philo);
		philo_eat(philo);
		philo_sleep();
		philo_think();
	}
}

void	pick_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data_ptr;
	pthread_mutex_lock(&(philo->left_fork));
	pthread_mutex_lock(&(data->done_lock));
	if (data->done == false)
		printf("%10ld\t%d\thas taken a left fork ⭕️\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_unlock(&(data->done_lock));
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&(data->done_lock));
	if (data->done == false)
		printf("%10ld\t%d\thas taken a right fork 🔴\n", \
		time_now() - data->start, philo->n_philo + 1);
	pthread_mutex_unlock(&(data->done_lock));
}

void	philo_eat(t_philo *philo)
{
	t_data		*data;
	long long	finish;

	data = philo->data_ptr;
	pthread_mutex_lock(&(data->check_meals_lock));
	philo->last_meal = time_now();
	pthread_mutex_lock(&(data->done));
	if (data->done == false)
		printf("%10ld\t%d\tis eating 🍧\n", \
		time_now() - data->start, philo->n_philo + 1);
	philo->times_eaten++;
	pthread_mutex_unlock(&(data->done_lock));
	finish = time_now() + data->time_to_eat; //not sure where to put it...
	while (time_now() < finish)
	{
		if (to_eat_or_not_to_eat(data) == 0) // have this function in every activity of the philo! sleeping and thinking too
			return ;
		usleep(100);
	}
}

void	philo_sleep(t_philo *philo)
{
	
}