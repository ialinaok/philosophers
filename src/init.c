/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:53:53 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/15 19:54:40 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	load_struct(data, argc, argv);
	pthread_mutex_init(&(data->be_or_not_lock), NULL);
	pthread_mutex_init(&(data->check_meals_lock), NULL);
	data->fork_arr = malloc(sizeof(pthread_mutex_t *) * data->n_philos);
	if (!data->fork_arr)
		return (-1);
	data->be_or_not = true;
	i = 0;
	while (i < data->n_philos)
	{
		data->philo_arr[i].n_philo = i;
		data->philo_arr[i].data_ptr = data;
		if (pthread_mutex_init(&(data->fork_arr[i]), NULL) != 0)
			return (-1);
		data->philo_arr[i].right_fork = &(data->fork_arr[i]);
		if (i == data->n_philos - 1)
			data->philo_arr[i].left_fork = &(data->fork_arr[0]);
		else
			data->philo_arr[i].left_fork = &(data->fork_arr[i + 1]);
		i++;
	}
	return (0);
}

void	load_struct(t_data *data, int argc, char **argv)
{
	data->n_philos = (int) ft_atoli(argv[1]);
	data->time_to_die = (int) ft_atoli(argv[2]);
	data->time_to_eat = (int) ft_atoli(argv[3]);
	data->time_to_sleep = (int) ft_atoli(argv[4]);
	if (argc == 6)
		data->n_meals = (int) ft_atoli(argv[5]);
	else
		data->n_meals = -1;
}
