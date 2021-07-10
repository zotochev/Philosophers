#include "philo_two.h"

/*
**	time_to_wait, mlsec
*/

void	ft_sleep(unsigned long time_to_wait)
{
	unsigned long	start;
	unsigned long	time_past;

	start = get_time_as_number();
	time_past = 0;
	while (time_past < time_to_wait)
	{
		usleep(400);
		time_past = get_time_as_number() - start;
	}
}

unsigned long	get_time_as_number(void)
{
	struct timeval	tp;

	if (-1 == gettimeofday(&tp, NULL))
		return (-1);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

unsigned long	get_time_as_timestamp(t_common *common)
{
	return (get_time_as_number() - common->start_time);
}
