#include "../../includes/builtins.h"

int	mini_exit(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;

    if (parser->str[1] != NULL)
    {
        printf("Error: exit call with too many arguments\n");
        return (1);
    }
    tools->exit = true;
    printf("exit\n");
	return (EXIT_SUCCESS);
}
