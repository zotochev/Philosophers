#include "philo_two.h"

int	main(int argc, char **argv)
{
	t_common	common;

	if (!common_init(argc, argv, &common)
		&& !forks_init(&common)
		&& !philosophers_init(&common))
	{
		threads_create(&common);
		supervisor_routine(&common);
		threads_join(&common);
	}
	return (0);
}
