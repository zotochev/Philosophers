#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//# define RED	"\x1B[31m"
//# define GREEN	"\x1B[32m"
//# define BLUE	"\x1B[34m"
//# define RESET	"\x1B[0m"

typedef struct s_philosopher
{
	int					number;
	pthread_t			thread;
	unsigned long		last_time_ate;
	int					count_eat;
	unsigned long		time;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		scheduler_served;
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

	pthread_mutex_t		is_dead;
	pthread_t			supervisor_thread;
	pthread_t			scheduler_thread;
	pthread_mutex_t		scheduler_start_plan;
	t_philosopher		*philo_list;
	pthread_mutex_t		*forks;
}				t_common;

void			threads_create(t_common *common);
void			threads_join(t_common *common);

void			*philosopher_routine(void *philosopher);
void			*supervisor_routine(void *philosopher);
void			*scheduler_routine(void *common_p);

int				is_args_valid(int argc, char **argv);
int				is_args_valid_after(t_common *common);
int				error_message(void);
int				error_message_malloc(size_t size);

int				common_init(int argc, char **argv, t_common *common);
int				philosophers_init(t_common *common);
int				forks_init(t_common *common);

int				is_digit(int c);
unsigned long	get_time_as_number(void);
unsigned long	get_time_as_timestamp(t_common *common);
int				ft_atoi(const char *str);
int				get_other_index(t_common *common, t_philosopher	*philo);

void			dying(t_philosopher *philo);
void			sleeping(t_philosopher *philo);
void			thinking(t_philosopher *philo);
int				eating(t_philosopher *philo);

void			ft_sleep(unsigned long time_to_wait);
void			check_dead(t_common *common);
int				next_philo(int count, int count_threads, void *common_p);

#endif
