#include "philo_three.h"

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
		if (!common->philo_list[count].scheduler_served)
			return (1);
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
	if (!is_args_valid_after(common) || open_semaphore(common)
		|| common->times_must_eat == 0)
		return (1);
	common->philo_list = malloc(
			sizeof(t_philosopher) * common->number_of_philosophers);
	common->philosophers_pid = malloc(
			sizeof(pid_t) * common->number_of_philosophers);
	if (NULL == common->philo_list || NULL == common->philosophers_pid)
		return (error_message_malloc(sizeof(t_philosopher)
				* common->number_of_philosophers));
	return (0);
}

int	open_semaphore(t_common *common)
{
	sem_unlink(SEM_IS_DEAD);
	common->is_dead = sem_open(SEM_IS_DEAD, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("kill");
	common->kill = sem_open("kill", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink(SEM_SCHEDULER_START);
	common->scheduler_start_plan = \
		sem_open(SEM_SCHEDULER_START, O_CREAT | O_EXCL, 0644, 0);
	sem_post(common->scheduler_start_plan);
	if (!common->is_dead || !common->kill || !common->scheduler_start_plan)
		return (1);
	return (0);
}

int	close_semaphore(sem_t *sem, char *sem_name)
{
	if (!sem_close(sem) && !sem_unlink(sem_name))
		return (0);
	return (1);
}

int	forks_init(t_common *common)
{
	sem_unlink(SEM_FORKS);
	common->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, 0);
	if (!common->forks)
		return (1);
	return (0);
}
