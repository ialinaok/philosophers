#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void	*myturn(void *arg)
{
	int	*iptr = (int *)arg; // void ptr and int ptr here point to the same var!
	for (int i = 0; i < *iptr; i++)
	{
		sleep(1);
		printf("my turn! %d -- %d\n", i, *iptr);
	}
	*iptr = *iptr + 1; // this allows me to do arithmetic on a void ptr
	return (arg);
}

void	yourturn()
{
	for (int i = 0; i < 5; i++)
	{
		sleep(1);
		printf("your turn! %d\n", i);
	}
}

int	main(void)
{
	pthread_t	myturnthread;
	int			counter;
	int			*ret;

	counter = 6;
	pthread_create(&myturnthread, NULL, myturn, &counter);
	// myturn();
	yourturn();
	pthread_join(myturnthread, (void *)&ret);
	printf("that's the counter:, and that's the return:\n");
	printf("                   %d                      %d\n", counter, *ret);
}

