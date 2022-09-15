/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:54 by apielasz          #+#    #+#             */
/*   Updated: 2022/09/15 19:31:10 by apielasz         ###   ########.fr       */
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
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		id;
	struct s_data	*data_ptr;
}						t_philo;

/**
 * @brief an overall struct with global data
 * @param n_philos is a total number of philos
 * @param who_finished is a status checker of all of
 * philosophers meal progress. it's mutexed with @param done_lock.
 * @param done is a flag set to true if philosopher dies or when
 * all philosophers finished their meals.
 * @param start is the beginning of the simulation
 * @param philo_list is a pointer to the first philosopher
 * (philosophers are in an array)
 */

typedef struct s_data
{
	int				n_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				n_meals;
	long long		start;
	int				who_finished;
	pthread_mutex_t	check_meals_lock;
	bool			be_or_not;
	pthread_mutex_t	be_or_not_lock;
	// struct s_philo	**philo_arr;
	struct s_philo	philo_arr[200];
	pthread_mutex_t	*fork_arr;
}					t_data;

// main.c
void	*routine_basic(void *arg);

// init.c
int			check_size(int argc, char **argv);
int			check_input(int argc, char **argv);
int			init(t_data *data, int argc, char **argv);
void		load_struct(t_data *data, int argc, char **argv);

// threads.c
int			start_simulation(t_data *data);
void		*unlimited(void *arg);
void		*limited(void *arg);

// philo.c
bool		to_be_or_not_to_be(t_data *data);
void		*routine(void *arg);
void		pick_forks(t_philo *philo);
bool		philo_eat(t_philo *philo);
bool		philo_sleep_think(t_philo *philo);
void		*one_philo_case(t_data *data);

// threads.c
int			start_simulation(t_data *data);
void		*unlimited(void *arg);
void		*limited(void *arg);
int			end_simulation(t_data *data);

// time.c
long long	time_now(void);

// utils.c
long		ft_atoli(const char *ptr);
int			ft_isdigit(int n);
int			err_msg(char *s);

#endif