
#include "philo.h"

void	ft_update_state(t_philo *philo, int state)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(table->m_state));
	if (philo->state != DEAD)
	{
		philo->state = state;
		if (state == EATING)
			gettimeofday(&(philo->last_meal), NULL);
		pthread_mutex_unlock(&(table->m_state));
		return ;
	}
	pthread_mutex_unlock(&(table->m_state));
}

static void	ft_print_state_msg(t_philo *philo, long time_stamp, int id,
	int *print_end)
{
	int	state;

	pthread_mutex_lock(&(philo->table->m_state));
	state = philo->state;
	pthread_mutex_unlock(&(philo->table->m_state));
	if (ft_everyone_is_full(philo->table))
		*print_end = 1;
	else if (state == DEAD)
	{
		printf("%5ld\t%d died\n", time_stamp, id);
		*print_end = 1;
	}
	else if (state == FORK && ft_everybody_alive(philo->table))
		printf("%5ld\t%d has taken a fork\n", time_stamp, id);
	else if (state == EATING)
		printf("%5ld\t%d is eating\n", time_stamp, id);
	else if (state == SLEEPING)
		printf("%5ld\t%d is sleeping\n", time_stamp, id);
	else if (state == THINKING)
		printf("%5ld\t%d is thinking\n", time_stamp, id);
}

void	ft_print_state(t_philo *philo)
{
	static int	print_end;
	long		time_stamp;
	int			id;

	time_stamp = ft_get_time_stamp(philo->start_time);
	id = philo->id;
	pthread_mutex_lock(&(philo->table->m_display));
	if (!print_end)
		ft_print_state_msg(philo, time_stamp, id, &print_end);
	pthread_mutex_unlock(&(philo->table->m_display));
}
