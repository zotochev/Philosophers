#include "philo_three.h"

int	is_digit(int c)
{
	return (c >= '0' && '9' >= c);
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

int	num_len(int n)
{
	int	result;

	result = (n < 0) + 2;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	int32_t		n_chars;
	int32_t		flag;

	n_chars = num_len(n);
	flag = 1;
	if (n < 0)
		flag = -flag;
	result = malloc(n_chars * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n < 0)
		*result = '-';
	n_chars--;
	result[n_chars--] = '\0';
	if (0 == n)
		result[0] = 48;
	while (0 != n)
	{
		result[n_chars--] = flag * (n % 10) + (48);
		n /= 10;
	}
	return (result);
}

int	get_other_index(t_common *common, t_philosopher	*philo)
{
	if (common->number_of_philosophers == 1)
		return (1);
	if (philo->number == common->number_of_philosophers - 1)
		return (0);
	else
		return (philo->number + 1);
}
