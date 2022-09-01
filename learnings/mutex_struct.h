#ifndef MUTEX_STRUCT_H
# define MUTEX_STRUCT_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
// # include <sys/time.h>

#define NUM 1000000UL

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
	int			how_many_meals;
	int			finished_all;
	long long	gong;
	struct s_philo	*philo_list;
}					t_big_brother;

typedef struct s_forks
{
	bool	fork1;
	bool	fork2;
	bool	fork3;
}					t_forks;

#endif