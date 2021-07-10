#include "philo_three.h"

void	threads_create(t_common *common)
{
	int	count;

	count = 0;
	common->scheduler_thread = fork();
	if (0 == common->scheduler_thread)
		scheduler_routine((void *)common);
	common->start_time = get_time_as_number();
	while (count < common->number_of_philosophers)
	{
		common->philosophers_pid[count] = fork();
		if (0 == common->philosophers_pid[count])
		{
			pthread_create(&common->philo_list[count].thread, NULL,
				philosopher_routine, &common->philo_list[count]);
			supervisor_routine((void *)(&common->philo_list[count]));
		}
		count++;
	}
}

void	threads_join(t_common *common)
{
	int		count;
	char	*sem_name;
	int		stat;

	count = 0;
	stat = 0;
	sem_wait(common->kill);
	if (common->times_must_eat <= 0)
		kill_all_processes(common);
	while (count < common->number_of_philosophers)
	{
		waitpid(common->philosophers_pid[count], &stat, WUNTRACED);
		if (stat == 1024)
			kill_all_processes(common);
		sem_name = common->philo_list[count].scheduler_served_name;
		close_semaphore(common->philo_list[count].scheduler_served, sem_name);
		count++;
	}
	close_semaphore(common->scheduler_start_plan, SEM_SCHEDULER_START);
	close_semaphore(common->is_dead, SEM_IS_DEAD);
	close_semaphore(common->forks, SEM_FORKS);
}

void	check_dead(t_common *common)
{
	sem_wait(common->is_dead);
	sem_post(common->is_dead);
}
