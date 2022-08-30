#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM 1000000UL

// all-seeing thread needs to be looking at and determining
// whether other philosophers can pick up certain forks!

typedef struct t_big_brother
{
	int			time_to_eat;
	int			finished_all;
}					s_big_brother;

typedef struct t_philo
{
	int			times_eaten;
	bool		finished;
	bool		*left_fork;
	bool		*right_fork;
	s_big_brother *big_ptr;
}						s_philo;

typedef struct s_forks
{
	bool	fork1;
	bool	fork2;
	bool	fork3;
}					t_forks;

void	*eat_first(void *arg)
{

}

int	main(void)
{
	t_forks		forks;

	t_big_brother	big_brother;

	pthread_t	philo1;
	pthread_t	philo2;
	pthread_t	philo3;

	s_philo		s_philo1;
	s_philo		s_philo2;
	s_philo		s_philo3;

	forks.fork1 = true;
	forks.fork2 = true;
	forks.forks3 = true;

	big_brother.finished_all = 0;
	big_brother.time_to_eat = 20; // in [ms]

	s_philo1.big_ptr = &big_brother;
	s_philo1.finished = 0;
	s_philo1.times_eaten = 0;
	s_philo1.left_fork = &forks.fork1;
	s_philo1.right_fork = &forks.fork3;

	s_philo2.big_ptr = &big_brother;
	s_philo2.finished = 0;
	s_philo2.times_eaten = 0;
	s_philo2.left_fork = &forks.fork2;
	s_philo2.right_fork = &fork.fork1;

	s_philo3.big_ptr = &big_brother;
	s_philo3.finished = 0;
	s_philo3.times_eaten = 0;
	s_philo3.left_fork = &forks.fork3;
	s_philo3.right_fork = &forks.fork2;
	pthread_create(&philo1, NULL, eat, &s_philo1);
}