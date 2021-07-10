#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# define SEM_IS_DEAD "is_dead"
# define SEM_SCHEDULER_START "scheduler_start_plan"
# define SEM_FORKS "forks"

typedef struct s_philosopher
{
	int					number;
	pthread_t			thread;
	unsigned long		last_time_ate;
	int					count_eat;
	unsigned long		time;
	sem_t				*scheduler_served;
	char				*scheduler_served_name;
	void				*common;
}				t_philosopher;

typedef struct s_common
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;

	unsigned long		start_time;

	pid_t				scheduler_thread;

	t_philosopher		*philo_list;
	pid_t				*philosophers_pid;
	sem_t				*forks;
	sem_t				*is_dead;
	sem_t				*scheduler_start_plan;
	sem_t				*kill;
}				t_common;

/*
**	Threading
*/

void			threads_create(t_common *common);
void			threads_join(t_common *common);
int				open_semaphore(t_common *common);
int				close_semaphore(sem_t *sem, char *sem_name);

/*
**	Validation
*/

int				is_args_valid(int argc, char **argv);
int				is_args_valid_after(t_common *common);
int				error_message(void);
int				error_message_malloc(size_t size);

/*
**	Init
*/

int				common_init(int argc, char **argv, t_common *common);
int				philosophers_init(t_common *common);
int				forks_init(t_common *common);

/*
**	Utils
*/

int				is_digit(int c);
unsigned long	get_time_as_number(void);
unsigned long	get_time_as_timestamp(t_common *common);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				get_other_index(t_common *common, t_philosopher	*philo);
void			ft_sleep(unsigned long time_to_wait);

/*
**	Routines
*/

void			*philosopher_routine(void *philosopher);
void			*supervisor_routine(void *philo);
void			*scheduler_routine(void *common_p);

void			dying(t_philosopher *philo);
void			sleeping(t_philosopher *philo);
void			thinking(t_philosopher *philo);
int				eating(t_philosopher *philo);

int				next_philo(int count, int count_threads, void *common_p);
int				count_cycle_increment(int count, int number_of_philosophers);
void			kill_all_processes(t_common *common);
void			when_dead(t_common *common, t_philosopher *philosopher);

void			check_dead(t_common *common);

#endif
