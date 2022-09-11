/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:54 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/11 13:43:26 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_INT 2147483647

/*
	* basic
	! yeah 
	? blue
	TODO still todo
*/

/**
 * @brief struct assigned to every philosopher
 * @param n_philo is philo's 'id'
 * @param id is an id of a thread
 */

typedef struct s_philo
{
	int				n_philo;
	int				times_eaten;
	// bool			finished_meals; - might be not needed when I compare the amount of meals
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		id;
	struct s_data	*data_ptr;
}						t_philo;

typedef struct s_fork
{
	int	i;
	pthread_mutex_t	fork; 
}					t_fork;

/**
 * @brief an overall struct with global data
 * @param n_philos is a total number of philos
 * @param finished_all is a status checker of all of
 * philosophers meal progress. it's mutexed.
 * @param start is the beginning of the simulation
 * @param philo_list is a pointer to the first philosopher
 * (philosophers are in an array)
 */

typedef struct s_data
{
	int			n_philos;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			n_meals;
	// int			finished_all; - might not be necessary if I compare with nmeals in the condition
	long long	start;
	struct s_philo	*philo_arr;
	struct s_fork	*fork_arr;
}					t_data;

// main.c

// init.c
int	check_size(int argc, char **argv);
int	check_input(int argc, char **argv);
int	init(t_data *data, int argc, char **argv);

// philo.c
void	*routine(void *arg);
int	create_threads(t_data *data);

// time.c
long long	time_now(void);
long long	time_passed(long long time);

// utils.c
size_t	ft_strlen(char *s);
long	ft_atoli(const char *ptr);
int		ft_isdigit(int n);
int		err_msg(char *s);

#endif