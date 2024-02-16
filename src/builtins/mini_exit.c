#include "../../includes/builtins.h"

int	check_exit_args(t_parser *parser)
{
	int	j;

	j = 0;
	while (parser->str[1][j])
	{
		if (!ft_isdigit(parser->str[1][j]))
			return (0);
		j++;
	}
	return (1);
}

int	mini_exit(t_tools *tools, t_parser *parser)
{
	int exit_number;

	(void)tools;
	exit_number = 0;
	if (parser->str[1])
	{
		if (parser->str[1])
		{ 
			if (!check_exit_args(parser))
			{
				exit_number = 255;
				printf("exit\nbash: exit: %s: numeric argument required\n", parser->str[1]);
				exit(exit_number);
			}
		}
		if (parser->str[2] != NULL)
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (1);
		}
		else
			exit_number = ft_atoi(parser->str[1]);
	}
	printf("exit\n");
	exit(exit_number);
}
