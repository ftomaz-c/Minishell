#include "../../includes/builtins.h"

int env(t_tools *tools, t_parser *command)
{
	int	i;

	i = 0;
	(void)tools;
	(void)command;
	while (tools->env[i])
		printf("%s\n", tools->env[i++]);
    return (0);
}