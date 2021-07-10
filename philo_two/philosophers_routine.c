#include "philo_two.h"

int	eating(t_philosopher *philo)
{
	check_dead((t_common *)(philo->common));
	if (philo->count_eat == ((t_common *)(philo->common))->times_must_eat)
		return (1);
	sem_wait(philo->scheduler_served);
	sem_wait(((t_common *)(philo->common))->forks);
	philo->time = get_time_as_timestamp((t_common *)(philo->common));
	check_dead((t_common *)(philo->common));
	printf("%10lu %d has taken a fork\n", philo->time, philo->number + 1);
	sem_wait(((t_common *)(philo->common))->forks);
	check_dead((t_common *)(philo->common));
	philo->time = get_time_as_timestamp((t_common *)(philo->common));
	printf("%10lu %d has taken a fork\n", philo->time, philo->number + 1);
	check_dead((t_common *)(philo->common));
	philo->last_time_ate = philo->time;
	printf("%10lu %d is eating\n", philo->time, philo->number + 1);
	ft_sleep(((t_common *)philo->common)->time_to_eat);
	sem_post(((t_common *)philo->common)->scheduler_start_plan);
	check_dead((t_common *)(philo->common));
	sem_post(((t_common *)(philo->common))->forks);
	sem_post(((t_common *)(philo->common))->forks);
	return (0);
}

void	sleeping(t_philosopher *philo)
{
	check_dead((t_common *)(philo->common));
	philo->time = get_time_as_timestamp((t_common *)(philo->common));
	printf("%10lu %d is sleeping\n", philo->time, philo->number + 1);
	ft_sleep(((t_common *)philo->common)->time_to_sleep);
	check_dead((t_common *)(philo->common));
}

void	thinking(t_philosopher *philo)
{
	check_dead((t_common *)(philo->common));
	printf("%10lu %d is thinking\n",
		get_time_as_timestamp(philo->common), philo->number + 1);
	check_dead((t_common *)(philo->common));
	philo->count_eat++;
}

void	dying(t_philosopher *philo)
{
	printf("%10lu %d died\n",
		get_time_as_timestamp(philo->common), philo->number + 1);
}
