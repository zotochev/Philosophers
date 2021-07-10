#include "philo_one.h"

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

int	ft_atoi(const char *str)
{
	int	flag;
	int	num;

	flag = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
		flag = -1;
	if (*str == 45 || *str == 43)
		str++;
	while (*str >= 48 && *str <= 57)
		num = num * 10 + (*str++ - 48);
	return (num * flag);
}

int	is_digit(int c)
{
	return (c >= '0' && '9' >= c);
}
