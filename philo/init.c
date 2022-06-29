
#include "philo.h"

static int	ft_free_all(t_table *table, int err)
{
	int	i;

	i = -1;
	while (++i < table->option.number_of_philosophers)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->m_display));
	pthread_mutex_destroy(&(table->m_all_alive));
	pthread_mutex_destroy(&(table->m_state));
	pthread_mutex_destroy(&(table->m_nb_meals));
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	return (err);
}

static int	ft_init_table_bis(t_table *table, t_option option, t_time time)
{
	int		i;
	t_philo	*philo;

	ft_init_philosophers(table, time);
	i = -1;
	while (++i < option.number_of_philosophers)
	{
		philo = table->philos + i;
		if (pthread_create(&(philo->thread), NULL, &ft_routine, philo))
			return (ft_free_all(table, ERROR_THREAD));
	}
	while (ft_all_alive_and_hungry(table) == CONTINUE)
		usleep(100);
	i = -1;
	while (++i < option.number_of_philosophers)
	{
		philo = table->philos + i;
		if (pthread_join(philo->thread, NULL))
			return (ft_free_all(table, ERROR_THREAD));
	}
	return (ft_free_all(table, SUCCESS));
}

static void	ft_init_global_mutex(t_table *table)
{
	pthread_mutex_init(&(table->m_display), NULL);
	pthread_mutex_init(&(table->m_all_alive), NULL);
	pthread_mutex_init(&(table->m_state), NULL);
	pthread_mutex_init(&(table->m_nb_meals), NULL);
}

int	ft_init_table(t_table *table, t_option option)
{
	int		i;
	t_time	time;

	if (gettimeofday(&time, NULL))
		return (ERROR_TIME);
	table->philos = malloc(sizeof(t_philo) * option.number_of_philosophers);
	table->forks = malloc(sizeof(t_mutex) * option.number_of_philosophers);
	table->option = option;
	table->all_alive = 1;
	if (!table->philos || !table->forks)
		return (ft_free_all(table, ERROR_ALLOC));
	i = -1;
	while (++i < option.number_of_philosophers)
		pthread_mutex_init(&(table->forks[i]), NULL);
	ft_init_global_mutex(table);
	return (ft_init_table_bis(table, option, time));
}
