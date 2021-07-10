#include "philo_one.h"

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

void	*when_dead(t_common *common, int count)
{
	pthread_mutex_lock(&common->is_dead);
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

void	*supervisor_routine(void *common_p)
{
	t_common		*cm;
	int				count;

	cm = (t_common *)common_p;
	count = 0;
	while (1)
	{
		while (count < cm->number_of_philosophers)
		{
			if ((get_time_as_timestamp(cm) - \
		cm->philo_list[count].last_time_ate >= (unsigned int) cm->time_to_die))
			{
				if ((cm->philo_list[count].count_eat == cm->times_must_eat)
					&& check_eat_done(cm))
					return (NULL);
				else if (cm->philo_list[count].count_eat != cm->times_must_eat)
					return (when_dead(cm, count));
			}
			count++;
		}
		count = 0;
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
		pthread_mutex_lock(&common->scheduler_start_plan);
		while (count_threads < common->number_of_philosophers - 1)
		{
			pthread_mutex_unlock(&common->philo_list[\
				next_philo(count, count_threads, common_p)].scheduler_served);
			count_threads += 2;
		}
		++count;
		if (count == common->number_of_philosophers)
			count = 0;
		ft_sleep(common->time_to_eat);
	}
	return (NULL);
}
