/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:37 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/27 14:30:24 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/* argv[1] - number of philos, argv[2] - time to die,
 to eat[3], to sleep[4], number of meals[5] */

/**
 * @brief function takes the arguments that were given to the program
 * and checks if the given values are correct
 * 
 * @param argc arg from main function
 * @param argv arg from main function
 * @return int -1 if given values are not correct
 */

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
		return (err_msg("\n✖️ that's too little philosophers. ✖️\n"));
	if (n_philos > 200)
		return (err_msg("\n✖️ that's too many philosophers. ✖️\n"));
	if (t_die > MAX_INT || t_eat > MAX_INT || t_sleep > MAX_INT)
		return (err_msg("\n✖️ given values are too big. ✖️\n"));
	if (argc == 6 && n_meals > MAX_INT)
		return (err_msg("\n✖️ wrong number of meals. just wrong. ✖️\n"));
	return (0);
}

/**
 * @brief function takes if given arguments contain only numbers
 * 
 * @param argv arg from main function
 * @return int -1 if other characters than digits were found
 */

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
				return (err_msg("\n✖️ only numbers, please. ✖️\n"));
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief function takes arguments from the main and checks if comply
 * with the rules given by subject
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (err_msg("\n✖️ wrong number of arguments. ✖️\n"));
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '-')
			return (err_msg("\n✖️ negative values? srsly? ✖️\n"));
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
