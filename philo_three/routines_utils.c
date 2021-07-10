#include "philo_three.h"

int	next_philo(int count, int count_threads, void *common_p)
{
	return ((count + count_threads) % \
		((t_common *)common_p)->number_of_philosophers);
}

int	count_cycle_increment(int count, int number_of_philosophers)
{
	count = count + 1;
	if (count == number_of_philosophers)
		return (0);
	return (count);
}

void	kill_all_processes(t_common *common)
{
	int	count;

	count = 0;
	while (count < common->number_of_philosophers)
	{
		kill(common->philosophers_pid[count], 9);
		count++;
	}
	kill(common->scheduler_thread, 9);
}

void	when_dead(t_common *common, t_philosopher *philosopher)
{
	sem_wait(common->is_dead);
	dying(philosopher);
	sem_post(common->kill);
	exit(4);
}
