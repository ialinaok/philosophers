#ifndef MUTEX_STRUCT_H
# define MUTEX_STRUCT_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

#define NUM 1000000UL

typedef struct s_philo
{
	int			times_eaten;
	bool		finished;
	bool		*left_fork;
	bool		*right_fork;
	int			n_philo;
	struct s_philo		*next;
	struct s_big_brother *big_ptr;
}						t_philo;

typedef struct s_big_brother
{
	int			time_to_eat;
	int			how_many_times;
	int			finished_all;
	struct s_philo		*first_philo;
}					t_big_brother;

typedef struct s_forks
{
	bool	fork1;
	bool	fork2;
	bool	fork3;
}					t_forks;

#endif