/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:53:53 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/14 11:28:52 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// number of philos - argv[1], time to die - argv[2] etc,
// to eat[3], to sleep[4], number of meals[5]

int	check_size(int argc, char **argv)
{
	long	n_philos;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	n_meals;

	n_philos = ft_atoli(argv[1]);
	t_die = ft_atoli(argv[2]);
	t_eat = ft_atoli(argv[3]);
	t_sleep = ft_atoli(argv[4]);
	if (argc == 6)
		n_meals = ft_atoli(argv[5]);
	if (n_philos < 1)
		return (err_msg("that's too little philosophers 🙆‍♀️\n"));
	if (t_die == 0 || t_eat == 0 || t_sleep == 0)
		return (err_msg("you can't give zeros, dude. 🙅‍♀️\n"));
	if (t_die > MAX_INT || t_eat > MAX_INT || t_sleep > MAX_INT)
		return (err_msg("given values are too big. 💁‍♀️\n"));
	if (argc == 6 && (n_meals < 1 || n_meals > MAX_INT))
		return (err_msg("wrong number of meals. just wrong. 🙅‍♀️\n"));
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (err_msg("wrong number of arguments. 🤷‍♀️\n"));
	while (argv[i] != NULL) // checks for negative values
	{
		if (argv[i][0] == '-')
			return (err_msg("negative values? srsly? 🙅‍♀️\n"));
		i++;
	}
	i = 1;
	while (argv[i] != NULL) // checks for alpha chars
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (err_msg("only numbers, please. 💁‍♀️\n"));
			j++;
		}
		i++;
	}
	if (check_size(argc, argv) == -1) // checks for proper sizes of values
		return (-1);
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	load_struct(data, argc, argv);
	pthread_mutex_init(&(data->be_or_not_lock), NULL);
	data->philo_arr = malloc (sizeof(t_philo *) * data->n_philos);
	if (!data->philo_arr)
		return (-1);
	data->fork_arr = malloc (sizeof(pthread_mutex_t *) * data->n_philos);
	if (!data->fork_arr)
		return (-1);
	data->be_or_not = false;
	while (i < data->n_philos)
	{
		data->philo_arr[i].n_philo = i;
		data->philo_arr[i].data_ptr = data;
		data->philo_arr[i].last_meal = time_now();
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
