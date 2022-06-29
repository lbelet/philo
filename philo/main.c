
#include "philo.h"

int	main(int argc, char **argv)
{
	t_option	option;
	t_table		table;

	if (ft_parse_option(&option, argc, argv))
		return (ft_print_help());
	return (ft_init_table(&table, option));
}
