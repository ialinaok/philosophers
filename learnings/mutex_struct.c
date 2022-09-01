#include "mutex_struct.h"

// all-seeing thread needs to be looking at and determining
// whether other philosophers can pick up certain forks!

long long	get_time_ms(void)
{
	long long		ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

void	*all_seeing(void *arg)
{
	t_big_brother	*big_struct;
	t_philo			*current_philo;
	int				local_times_ate;

	local_times_ate = 0;
	big_struct = (t_big_brother*)arg;
	while (local_times_ate != big_struct->how_many_meals)
	{
		current_philo = big_struct->philo_list;
		while (current_philo->next != NULL)
		{
			if (current_philo->times_eaten == big_struct->how_many_meals)
				local_times_ate++;
			current_philo = current_philo->next;
		}
	}
	return (NULL);
}

void	*eating(void *arg)
{
	t_philo	*philo;
	pthread_mutex_t	lock;

	philo = (t_philo *)arg;
	pthread_mutex_init(&lock, NULL);
	while (philo->times_eaten != philo->big_ptr->how_many_meals)
	{
		if (*philo->left_fork == true && *philo->right_fork == true)
		{
			pthread_mutex_lock(&lock);
			philo->right_fork = false;
			philo->left_fork = false;
			sleep(philo->big_ptr->time_to_eat);
			philo->times_eaten++;
			printf("philosopher %d is eating for the %d time\n", philo->number_of_philo, philo->times_eaten);
			*philo->right_fork = true;
			*philo->left_fork = true;
			pthread_mutex_unlock(&lock);
		}
	}
	return (NULL);
}

void	create_philo_list(t_big_brother *big)
{

}

int	main(void)
{
	t_big_brother	big_brother;
	int				n; //number of philos, now here, in the future passed to program

	n = 4;
	create_philo_list(&big_brother, n);
	big_brother.finished_all = 0;
	big_brother.time_to_eat = 2; // in [s] for now
	big_brother.how_many_meals = 3;
	// big_brother.philo_list = &s_philo1;

// philo struct init

	// s_philo1.big_ptr = &big_brother;
	// s_philo1.n_philo = 1;
	// s_philo1.finished_eating = 0;
	// s_philo1.times_eaten = 0;
	// s_philo1.left_fork = &forks.fork1;
	// s_philo1.right_fork = &forks.fork3;
	// s_philo1.next = &s_philo2;

	// s_philo2.big_ptr = &big_brother;
	// s_philo2.n_philo = 2;
	// s_philo2.finished_eating = 0;
	// s_philo2.times_eaten = 0;
	// s_philo2.left_fork = &forks.fork2;
	// s_philo2.right_fork = &forks.fork1;
	// s_philo2.next = &s_philo3;

	// s_philo3.big_ptr = &big_brother;
	// s_philo3.n_philo = 3;
	// s_philo3.finished_eating = 0;
	// s_philo3.times_eaten = 0;
	// s_philo3.left_fork = &forks.fork3;
	// s_philo3.right_fork = &forks.fork2;
	// s_philo3.next = NULL;

// start - get the time that you will then relate to for meals and stuff
	// pthread_create(&eye, NULL, all_seeing, &big_brother);

	// pthread_create(&philo1, NULL, eating, &s_philo1);
	// pthread_create(&philo2, NULL, eating, &s_philo2);
	// pthread_create(&philo3, NULL, eating, &s_philo3);
}