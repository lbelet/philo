
#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define FORMAT -2
# define SUCCESS 0
# define ERROR_THREAD 1
# define ERROR_ALLOC 2
# define ERROR_TIME 3
# define ERROR_PARSE 4
# define EATING 5
# define SLEEPING 6
# define THINKING 7
# define FORK 8
# define DEAD 9
# define CONTINUE 10
# define STOP 11

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

typedef struct s_option
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}			t_option;

typedef struct s_table
{
	t_mutex				m_display;
	t_mutex				m_state;
	t_mutex				m_all_alive;
	t_mutex				m_nb_meals;
	t_mutex				*forks;
	t_option			option;
	struct s_philo		*philos;
	int					all_alive;
}						t_table;

typedef struct s_philo
{
	int			id;
	int			fork_left;
	int			fork_right;
	int			state;
	int			nb_meals;
	t_table		*table;
	t_time		last_meal;
	t_time		start_time;
	pthread_t	thread;
}				t_philo;

int		ft_parse_option(t_option *option, int argc, char **argv);
int		ft_print_help(void);
int		ft_init_table(t_table *table, t_option option);
void	ft_init_philosophers(t_table *table, t_time time);
long	ft_get_time_stamp(t_time start);
void	ft_print_state(t_philo *philo);
int		ft_waiting(long to_wait, t_table *table);
void	*ft_routine(void *param);
int		ft_everybody_alive(t_table *table);
int		ft_everyone_is_full(t_table *table);
int		ft_all_alive_and_hungry(t_table *table);
void	ft_update_state(t_philo *philo, int state);

#endif
