#include "philo_one.h"

void	threads_create(t_common *common)
{
	int	count;

	count = 0;
	pthread_create(&common->scheduler_thread, NULL, scheduler_routine, common);
	pthread_detach(common->scheduler_thread);
	common->start_time = get_time_as_number();
	while (count < common->number_of_philosophers)
	{
		pthread_create(&common->philo_list[count].thread, NULL,
			philosopher_routine, &common->philo_list[count]);
		pthread_detach(common->philo_list[count].thread);
		count++;
	}
}

void	threads_join(t_common *common)
{
	int	count;

	count = 0;
	pthread_join(common->supervisor_thread, NULL);
	pthread_join(common->scheduler_thread, NULL);
	while (count < common->number_of_philosophers)
	{
		pthread_join(common->philo_list[count].thread, NULL);
		pthread_mutex_destroy(&common->forks[count]);
		count++;
	}
	pthread_mutex_destroy(&common->scheduler_start_plan);
}

int	philosophers_init(t_common *common)
{
	int	count;

	count = 0;
	while (count < common->number_of_philosophers)
	{
		common->philo_list[count].number = count;
		common->philo_list[count].time = 0;
		common->philo_list[count].last_time_ate = 0;
		common->philo_list[count].count_eat = 0;
		common->philo_list[count].common = common;
		pthread_mutex_init(
			&common->philo_list[count].scheduler_served, NULL);
		pthread_mutex_lock(&common->philo_list[count].scheduler_served);
		common->philo_list[count].fork_left = &(common->forks[count]);
		common->philo_list[count].fork_right = &(common->forks[
				get_other_index(common, &common->philo_list[count])]);
		count++;
	}
	return (0);
}

int	common_init(int argc, char **argv, t_common *common)
{
	if (!is_args_valid(argc, argv))
		return (1);
	common->number_of_philosophers = ft_atoi(argv[1]);
	common->time_to_die = ft_atoi(argv[2]);
	common->time_to_eat = ft_atoi(argv[3]);
	common->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		common->times_must_eat = ft_atoi(argv[5]);
		if (common->times_must_eat < 0)
			return (error_message());
	}
	else
		common->times_must_eat = -1;
	if (!is_args_valid_after(common) || common->times_must_eat == 0)
		return (1);
	common->philo_list = malloc(
			sizeof(t_philosopher) * common->number_of_philosophers);
	if (NULL == common->philo_list)
		return (error_message_malloc(sizeof(t_philosopher)
				* common->number_of_philosophers));
	pthread_mutex_init(&common->is_dead, NULL);
	pthread_mutex_init(&common->scheduler_start_plan, NULL);
	return (0);
}

int	forks_init(t_common *common)
{
	int					count;
	pthread_mutex_t		*forks;
	int					num_of_forks;

	count = 0;
	if (common->number_of_philosophers == 1)
		num_of_forks = 1;
	else
		num_of_forks = common->number_of_philosophers;
	forks = malloc(sizeof(pthread_mutex_t) * num_of_forks);
	if (NULL == forks)
		return (error_message_malloc(sizeof(pthread_mutex_t) * num_of_forks));
	while (count < num_of_forks)
	{
		if (0 != pthread_mutex_init(&forks[count], NULL))
			return (error_message());
		count++;
	}
	common->forks = forks;
	return (0);
}
