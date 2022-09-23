/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:37 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/23 15:13:40 by apielasz         ###   ########.fr       */
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
		return (err_msg("✖️ that's too little philosophers. ✖️\n"));
	if (n_philos > 200)
		return (err_msg("✖️ that's too many philosophers. ✖️\n"));
	// if (t_eat == 0 || t_sleep == 0)
	// 	return (err_msg("✖️ you can't give zeros, dude. ✖️"));
	if (t_die > MAX_INT || t_eat > MAX_INT || t_sleep > MAX_INT)
		return (err_msg("✖️ given values are too big. ✖️\n"));
	// if (argc == 6 && (n_meals < 1 || n_meals > MAX_INT))
	if (argc == 6 && n_meals > MAX_INT)
		return (err_msg("✖️ wrong number of meals. just wrong. ✖️\n"));
	return (0);
}

int	check_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (err_msg("✖️ only numbers, please. ✖️\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (err_msg("✖️ wrong number of arguments. ✖️\n"));
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '-')
			return (err_msg("✖️ negative values? srsly? ✖️\n"));
		i++;
	}
	if (check_number(argv) == -1)
		return (-1);
	if (check_size(argc, argv) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv) == -1)
		return (1);
	if (init(&data, argc, argv) == -1)
		return (2);
	if (start_simulation(&data) == -1)
		return (3);
	end_simulation(&data);
}
