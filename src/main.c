/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:37 by apielasz          #+#    #+#             */
/*   Updated: 2022/08/31 21:06:57 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	show_error_message(char *s)
{
	write(2, s, ft_strlen(s));
	return (1);
}

int	check_input(int argc, char **argv, t_big_brother *big_bro)
{
	if (argc != 5 || argc != 6)
		return (show_error_message("incorrect number of arguments for the program\n"));
	big_bro->time_to_eat
}

int	main(int argc, char **argv)
{
	t_big_brother	big_bro;

	if (check_input(argc, argv, &big_bro) == 1)
		return (show_error_message("incorrect input\n"));
}