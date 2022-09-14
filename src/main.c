/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:37 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/14 17:24:41 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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