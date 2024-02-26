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
	if (parser->str[1])
	{
		if (parser->str[1])
		{ 
			if (!check_exit_args(parser))
			{
				global_status = 2;
				tools->exit = 255;
				printf("exit\nbash: exit: %s: numeric argument required\n", parser->str[1]);
				return(global_status);
			}
		}
		if (parser->str[2] != NULL)
		{
			printf("exit\nbash: exit: too many arguments\n");
			global_status = EXIT_FAILURE;
			return (global_status);
		}
		else
			tools->exit = ft_atoi(parser->str[1]);
	}
	printf("exit\n");
	tools->exit = 1;
	global_status = EXIT_SUCCESS;
	return (global_status);
}
