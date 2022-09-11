/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:37:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/11 16:28:30 by apielasz         ###   ########.fr       */
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
		pick_forks();
		philo_eat();
		philo_sleep();
		philo_think();
	}
}
