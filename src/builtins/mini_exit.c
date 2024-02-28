#include "../../includes/builtins.h"

long long	check_if_within_range(char *status)
{
	long long	nbr;

	nbr = ft_atoll(status);
	if (errno == ERANGE)
		nbr = 0;
	return (nbr);
}

int	check_exit_args(t_parser *parser)
{
	int	is_zero;
	int	j;

	j = 0;
	is_zero = 0;
	while (ft_isspace(parser->str[1][j]))
		j++;
	if (!parser->str[1][j])
		return (0);
	if (parser->str[1][j] == '+' || parser->str[1][j] == '-')
		j++;
	if (!parser->str[1][j])
		return (0);
	while (ft_isdigit(parser->str[1][j]))
		j++;
	if (parser->str[1][j - 1] == '0')
		is_zero = 1;
	while (ft_isspace(parser->str[1][j]))
		j++;
	if (parser->str[1][j])
		return (0);
	if (!check_if_within_range(parser->str[1]) && !is_zero)
		return (0);
	return (1);
}

void	exit_err(int err, char *str)
{
	if (err == 1)
	{
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	}
	else if (err == 2)
	{
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
}

int	mini_exit(t_tools *tools, t_parser *parser)
{
	if (parser->str[1])
	{
		if (parser->str[1])
		{
			if (!check_exit_args(parser))
			{
				global_status = 2;
				tools->exit = 255;
				exit_err(2, parser->str[1]);
				return(global_status);
			}
			else
				global_status = ft_atoi(parser->str[1]);
		}
		if (parser->str[2] != NULL)
		{
			global_status = EXIT_FAILURE;
			exit_err(1, parser->str[0]);
			return (global_status);
		}
	}
	tools->exit = 1;
	return (global_status);
}
