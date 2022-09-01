/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:54 by apielasz          #+#    #+#             */
/*   Updated: 2022/08/31 21:07:56 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			number_of_philo;
	int			times_eaten;
	bool		finished_eating;
	bool		*left_fork;
	bool		*right_fork;
	pthread_t	id;
	struct s_philo		*next;
	struct s_big_brother *big_ptr;
}						t_philo;

typedef struct s_big_brother
{
	int			philos_amount;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			how_many_meals;
	int			finished_all;
	long long	gong;
	struct s_philo	*philo_list;
}					t_big_brother;

// philosophers.c
int	show_error_message(char *s);

// utils.c
size_t	ft_strlen(char *s);

#endif