#include "philo_three.h"

int	error_message(void)
{
	printf("Something wrong\n");
	return (1);
}

int	error_message_malloc(size_t size)
{
	printf("Requested amount of memory is to big %lu\n", size);
	return (1);
}

int	is_args_valid(int argc, char **argv)
{
	int	cnt;
	int	cnt_arg;

	cnt = 1;
	cnt_arg = 0;
	if (argc < 5 || argc > 6)
		printf("Wrong number of arguments\n");
	if (argc < 5 || argc > 6)
		return (0);
	while (cnt < argc)
	{
		while (argv[cnt][cnt_arg])
		{
			if (!is_digit(argv[cnt][cnt_arg]) && '-' != argv[cnt][cnt_arg]
				&& '+' != argv[cnt][cnt_arg])
			{
				printf("None numerical argument: \"%s\"\n", argv[cnt]);
				return (0);
			}
			cnt_arg++;
		}
		cnt_arg = 0;
		cnt++;
	}
	return (1);
}

int	is_args_valid_after(t_common *common)
{
	if (common->number_of_philosophers <= 0)
	{
		printf("Wrong argument: \"%d\"\n", common->number_of_philosophers);
		return (0);
	}
	if (common->time_to_die < 0)
	{
		printf("Wrong argument: \"%d\"\n", common->number_of_philosophers);
		return (0);
	}
	if (common->time_to_eat < 0)
	{
		printf("Wrong argument: \"%d\"\n", common->number_of_philosophers);
		return (0);
	}
	if (common->time_to_sleep < 0)
	{
		printf("Wrong argument: \"%d\"\n", common->number_of_philosophers);
		return (0);
	}
	return (1);
}
