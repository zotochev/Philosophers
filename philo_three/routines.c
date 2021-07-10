#include "philo_three.h"

void	*philosopher_routine(void *philosopher)
{
	while (1)
	{
		if (eating((t_philosopher *)philosopher))
			break ;
		sleeping(((t_philosopher *)philosopher));
		thinking(((t_philosopher *)philosopher));
	}
	return (NULL);
}

void	*supervisor_routine(void *philo)
{
	t_common		*common;
	t_philosopher	*philosopher;

	common = (t_common *)(((t_philosopher *)philo)->common);
	philosopher = (t_philosopher *)philo;
	while (1)
	{
		if ((get_time_as_timestamp(common) - philosopher->last_time_ate >= \
			(unsigned long)common->time_to_die))
		{
			if (philosopher->count_eat == common->times_must_eat)
			{
				sem_post(common->kill);
				exit(0);
			}
			else
				when_dead(common, philosopher);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*scheduler_routine(void *common_p)
{
	int				count;
	int				count_threads;
	t_common		*common;

	count = 0;
	common = (t_common *)common_p;
	while (1)
	{
		count_threads = 0;
		sem_wait(common->scheduler_start_plan);
		while (count_threads < common->number_of_philosophers - 1)
		{
			sem_post(common->philo_list[\
				next_philo(count, count_threads, common_p)].scheduler_served);
			sem_post(common->forks);
			sem_post(common->forks);
			count_threads += 2;
		}
		count = count_cycle_increment(count, common->number_of_philosophers);
		ft_sleep(common->time_to_eat);
	}
	sem_post(common->kill);
	return (NULL);
}
