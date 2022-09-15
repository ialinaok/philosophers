/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialinaok <ialinaok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:19:23 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/15 21:36:27 by ialinaok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
		return (1);
	else
		return (0);
}

/**
 * @brief function takes a string, prints it
 * as error message and returns -1
 * @param s wanted error message
 * @return error int
 */

int	err_msg(char *s)
{
	printf("%s\n", s);
	return (-1);
}

/**
 * @brief function returns the current time in ms
 * @return is current time in miliseconds
 */

long long	time_now(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}
