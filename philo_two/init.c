#include "philo_two.h"

void	threads_create(t_common *common)
{
	int	count;

	count = 0;
	pthread_create(&common->scheduler_thread, NULL,
		scheduler_routine, common);
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

/*
**	int 	count;
**	char	*sem_name;
**
**	count = 0;
**	pthread_join(common->supervisor_thread, NULL);
**	pthread_join(common->scheduler_thread, NULL);
**	while (count < common->number_of_philosophers)
**	{
**		pthread_join(common->philo_list[count].thread, NULL);
**		sem_name = common->philo_list[count].scheduler_served_name;
**		close_semaphore(common->philo_list[count].scheduler_served, sem_name);
**		count++;
**	}
*/

void	threads_join(t_common *common)
{
	close_semaphore(common->scheduler_start_plan, SEM_SCHEDULER_START);
	close_semaphore(common->is_dead, SEM_IS_DEAD);
	close_semaphore(common->forks, SEM_FORKS);
}

int	philosophers_init(t_common *common)
{
	int		count;
	char	*sem_name;

	count = 0;
	while (count < common->number_of_philosophers)
	{
		common->philo_list[count].number = count;
		common->philo_list[count].time = 0;
		common->philo_list[count].last_time_ate = 0;
		common->philo_list[count].count_eat = 0;
		common->philo_list[count].common = common;
		sem_name = ft_itoa(count);
		common->philo_list[count].scheduler_served_name = sem_name;
		sem_unlink(sem_name);
		common->philo_list[count].scheduler_served = \
			sem_open(sem_name, O_CREAT | O_EXCL, 0644, 0);
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
	open_semaphore(common);
	return (0);
}
