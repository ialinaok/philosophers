/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialinaok <ialinaok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:54 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/06 11:04:47 by ialinaok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

/*
	* basic
	! yeah 
	? blue
	TODO still todo
*/

typedef struct s_philo
{
	int			n_philo;
	int			times_eaten;
	// bool		finished_meals; - might be not needed when I compare the amount of meals
	bool		*left_fork;
	bool		*right_fork;
	pthread_t	id;
	struct s_big_brother *big_ptr;
}						t_philo;

typedef struct s_big_brother
{
	int			n_philos;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			n_meals;
	int			finished_all;
	long long	gong;
	struct s_philo	*philo_list;
}					t_big_brother;

// main.c

// utils.c
size_t	ft_strlen(char *s);
int	ft_atoi(const char *ptr);
int	show_error_message(char *s);

// time.c
long long	time_now(void);
long long	time_passed(long long time);

#endif