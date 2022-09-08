/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:19:23 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/08 21:10:59 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../inc/philosophers.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/**
 * @brief function converts the initial portion of the string
 * pointed to by ptr to int representation
 * @param ptr 
 * @return long 
 */

long	ft_atoli(const char *ptr)
{
	int		i;
	int		sign;
	long	count;

	i = 0;
	sign = 1;
	count = 0;
	while (ptr[i] == '\t' || ptr[i] == '\n' || ptr[i] == '\v'
		|| ptr[i] == '\f' || ptr[i] == '\r' || ptr[i] == ' ')
		i++;
	if ((ptr[i] == '-') || (ptr[i] == '+'))
	{
		sign = 44;
		sign = sign - ptr[i++];
	}
	while ((ptr[i] >= 48) && (ptr[i] <= 57))
		count = count * 10 + (ptr[i++] - '0');
	return (count * sign);
}

/**
 * @brief function tests for a decimal digit character
 * @param n is the character to be checked
 * @return 1 if char is a digit, 0 if not
 */

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * @brief function takes a string, prints it
 * as error message and returns -1
 * @param s wanted error message
 * @return error int
 */

int	err_msg(char *s)
{
	printf("%s\n");
	return (-1);
}
