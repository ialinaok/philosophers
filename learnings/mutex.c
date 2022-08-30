//after using the mutex lock, we get the correct result,
//but execution is waaay slower.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 1000000UL
uint32_t counter = 0;
pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

void	*count_to_number(void *arg)
{
	for (uint32_t i = 0; i < NUM; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t;

	pthread_create(&t, NULL, count_to_number, NULL);
	count_to_number(NULL);
	pthread_join(t, NULL);
	printf("done counting, count = %u\n", counter);
}