/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:23:33 by ialinaok          #+#    #+#             */
/*   Updated: 2022/09/08 17:02:12 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief function returns the current time in ms
 * @return is current time in miliseconds
 */

long long	time_now(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

/**
 * 
 * @brief function calculates the time passed from the
 * given time to current time
 * @param time is the given time
 * @return is the time passed
 */

long long	time_passed(long long time)
{
	long long		time_passed;
	long long		current_time;
	struct timeval	tv;

	time_passed = 0;
	current_time = time_now;
	time_passed = current_time - time;
	return (time_passed);
}