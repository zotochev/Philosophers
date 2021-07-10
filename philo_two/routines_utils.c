#include "philo_two.h"

void	*when_dead(t_common *common, int count)
{
	sem_wait(common->is_dead);
	dying(&common->philo_list[count]);
	return (NULL);
}

int	check_eat_done(t_common *common)
{
	int	count;

	count = 0;
	while (count < common->number_of_philosophers)
	{
		if (common->philo_list[count].count_eat != common->times_must_eat)
			return (0);
		count++;
	}
	return (1);
}

int	count_cycle_increment(int count, int number_of_philosophers)
{
	count = count + 1;
	if (count == number_of_philosophers)
		return (0);
	return (count);
}

int	next_philo(int count, int count_threads, void *common_p)
{
	return ((count + count_threads) % \
		((t_common *)common_p)->number_of_philosophers);
}

void	check_dead(t_common *common)
{
	sem_wait(common->is_dead);
	sem_post(common->is_dead);
}
