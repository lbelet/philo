
#include "philo.h"

static int	ft_start_eating(t_philo *philo)
{
	ft_update_state(philo, FORK);
	pthread_mutex_lock(&(philo->table->forks[philo->fork_left]));
	ft_print_state(philo);
	pthread_mutex_lock(&(philo->table->forks[philo->fork_right]));
	ft_print_state(philo);
	ft_update_state(philo, EATING);
	ft_print_state(philo);
	return (ft_waiting(philo->table->option.time_to_eat, philo->table));
}

static int	ft_start_sleeping(t_philo *philo)
{
	if (!ft_everybody_alive(philo->table))
		return (STOP);
	ft_update_state(philo, SLEEPING);
	ft_print_state(philo);
	return (ft_waiting(philo->table->option.time_to_sleep, philo->table));
}

static void	ft_routine_one(t_philo *philo)
{
	ft_update_state(philo, FORK);
	pthread_mutex_lock(&(philo->table->forks[philo->fork_left]));
	ft_print_state(philo);
	ft_waiting(philo->table->option.time_to_die, philo->table);
	ft_update_state(philo, DEAD);
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
}

void	ft_routine_loop(t_philo *philo)
{
	int	status;

	if (philo->fork_left == philo->fork_right)
	{
		ft_routine_one(philo);
		return ;
	}
	status = ft_start_eating(philo);
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->fork_right]));
	if (status == STOP)
		return ;
	pthread_mutex_lock(&(philo->table->m_nb_meals));
	philo->nb_meals++;
	pthread_mutex_unlock(&(philo->table->m_nb_meals));
	if (ft_start_sleeping(philo) == STOP)
		return ;
	ft_update_state(philo, THINKING);
	ft_print_state(philo);
}

void	*ft_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (ft_all_alive_and_hungry(philo->table) == STOP)
			break ;
		ft_routine_loop(philo);
		usleep(100);
	}
	return (NULL);
}
