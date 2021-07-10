#include "philo_one.h"

int	get_other_index(t_common *common, t_philosopher	*philo)
{
	if (common->number_of_philosophers == 1)
		return (1);
	if (philo->number == common->number_of_philosophers - 1)
		return (0);
	else
		return (philo->number + 1);
}

void	check_dead(t_common *common)
{
	pthread_mutex_lock(&common->is_dead);
	pthread_mutex_unlock(&common->is_dead);
}

int	next_philo(int count, int count_threads, void *common_p)
{
	return ((count + count_threads) % \
		((t_common *)common_p)->number_of_philosophers);
}
