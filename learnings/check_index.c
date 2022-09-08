#include <stdio.h>
#include <stdlib.h>

typedef struct	s_philo
{
	int				i;
	struct s_philo	*next;
}				t_philo;

void	spawn_philos(t_philo *philo, int n)
{
	// t_philo	*temp;
	int	i = 0;

	// temp = *philo;/
	while (i < n)
	{
		philo[i].i = i;
		printf("the i is: %d\n", i);
		i++;
	}
}

int	main(void)
{
	t_philo	*philo;
	int		n = 5;
	int		i = 0;

	philo = (t_philo *)malloc(sizeof(t_philo) * n);
	if (philo == NULL)
		return (1);
	spawn_philos(philo, n);
	i = 0;
	while (i < n)
	{
		printf("%d philo: %d\n", i, philo[i].i);
		i++;
	}
	return (0);
}