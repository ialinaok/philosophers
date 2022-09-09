/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:37:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/09 19:01:38 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->n_philo % 2 == 0)
		usleep(10 * 1000);
	printf("philosopher [%d] starts eating 😋\n", philo->n_philo);
	usleep(philo->data_ptr->time_to_eat);
	printf("philosopher [%d] finished eating 🤰\n", philo->n_philo);
	return (NULL);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&(data->philo_arr[i].id), NULL, &routine, &(data->philo_arr[i]));
		printf("%dth philosopher's thread started.\n", data->philo_arr[i].n_philo);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philo_arr[i].id, NULL);
		printf("%dth philosopher's thread finished execution.\n", data->philo_arr[i].n_philo);
		i++;
	}
	return (0);
}