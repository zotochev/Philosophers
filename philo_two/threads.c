#include "philo_two.h"

int	open_semaphore(t_common *common)
{
	sem_unlink(SEM_IS_DEAD);
	common->is_dead = sem_open(SEM_IS_DEAD, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(SEM_SCHEDULER_START);
	common->scheduler_start_plan = \
		sem_open(SEM_SCHEDULER_START, O_CREAT | O_EXCL, 0644, 0);
	sem_post(common->scheduler_start_plan);
	if (!common->is_dead || !common->scheduler_start_plan)
		return (1);
	return (0);
}

int	forks_init(t_common *common)
{
	sem_unlink(SEM_FORKS);
	common->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, 0);
	return (0);
}

int	close_semaphore(sem_t *sem, char *sem_name)
{
	if (!sem_close(sem) && !sem_unlink(sem_name))
		return (0);
	printf("Failed to close semaphore %s\n", sem_name);
	return (1);
}
