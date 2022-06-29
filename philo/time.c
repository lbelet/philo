
#include "philo.h"

static long	ft_get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_get_time_stamp(t_time start)
{
	long	t;
	long	s;

	t = ft_get_time();
	s = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (t - s);
}

int	ft_waiting(long to_wait, t_table *table)
{
	long int	current;

	current = ft_get_time();
	while (ft_get_time() < current + to_wait
		&& ft_everybody_alive(table) == CONTINUE)
		usleep(100);
	return (ft_everybody_alive(table));
}
