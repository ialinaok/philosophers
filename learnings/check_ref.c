#include <stdio.h>
#include <stdlib.h>

typedef struct	s_philo
{
	int				i;
	struct s_philo	*next;
	struct s_philo	*first;
}				t_philo;

void	spawn_philos(t_philo **philo, int n)
{
	t_philo	*temp;
	int		i = 0;

	temp = *philo;
	while (i < n)
	{
		// printf("%d\n", temp->i);
		// temp->i = i;
		// temp = temp->next;
		i++;
	}
}

int	main(void)
{
	t_philo	*philo;
	t_philo	**first;
	int		i = 0;
	int		n = 5;

	first = &philo;
	philo = malloc(sizeof(t_philo *));
	while (i < n)
	{
		// philo->i = i;
		philo->first = first;
		philo->next = malloc(sizeof(t_philo *));
		philo = philo->next;
		i++;
	}
	philo->next = NULL;
	philo = philo->first;
	spawn_philos(&philo, n);
	i = 0;
	// while (i < 0 || philo)
	// {
	// 	printf("%d philo: %d\n", i, philo->i);
	// 	i++;
	// 	philo = philo->next;
	// }
}