/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:37 by apielasz          #+#    #+#             */
/*   Updated: 2022/08/24 17:22:22 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	show_error_message(char *s)
{
	write(2, s, ft_strlen(s));
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		return (show_error_message("Incorrect number of arguments\n"));
}