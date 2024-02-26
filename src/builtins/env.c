#include "../../includes/builtins.h"

int	env(t_tools *tools, t_parser *command)
{
	int	i;

	i = 0;
	(void)tools;
	(void)command;
	while (tools->env[i])
	{
		if (!ft_strchr(tools->env[i], '='))
			i++;
		else
		{
			if (!tools->env[i])
				break ;
			printf("%s\n", tools->env[i]);
			i++;
		}
	}
	global_status = EXIT_SUCCESS;
	return (global_status);
}
