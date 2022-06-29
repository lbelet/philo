
#include "philo.h"

int	ft_print_help(void)
{
	printf("Usage error 404 ;-)\n");
	return (SUCCESS);
}

static int	ft_atoi(char *nptr)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	if (nptr[0] < '0' || nptr[0] > '9')
		return (FORMAT);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = 10 * nb + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0' || nb > 2147483647 || i > 10)
		return (FORMAT);
	return ((int)nb);
}

int	ft_parse_option(t_option *option, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ERROR_PARSE);
	option->number_of_philosophers = ft_atoi(argv[1]);
	option->time_to_die = ft_atoi(argv[2]);
	option->time_to_eat = ft_atoi(argv[3]);
	option->time_to_sleep = ft_atoi(argv[4]);
	option->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		option->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (option->number_of_philosophers == FORMAT
		|| option->time_to_die == FORMAT
		|| option->time_to_eat == FORMAT || option->time_to_sleep == FORMAT
		|| option->number_of_times_each_philosopher_must_eat == FORMAT)
		return (ERROR_PARSE);
	return (SUCCESS);
}
