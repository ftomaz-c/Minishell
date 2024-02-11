#include "../../includes/builtins.h"

void	execute_builtin(t_tools *tools)
{
	if (ft_strncmp(tools->parser->str[0], "cd", ft_strlen(tools->parser->str[0])) == 0)
		cd(tools, tools->parser);
	else if (ft_strncmp(tools->parser->str[0], "pwd", ft_strlen(tools->parser->str[0])) == 0)
		pwd(tools, tools->parser);
	else if (ft_strncmp(tools->parser->str[0], "env", ft_strlen(tools->parser->str[0])) == 0)
		env(tools, tools->parser);
	else if (ft_strncmp(tools->parser->str[0], "echo", ft_strlen(tools->parser->str[0])) == 0)
		echo(tools, tools->parser);
	else if (ft_strncmp(tools->parser->str[0], "exit", ft_strlen(tools->parser->str[0])) == 0)
		mini_exit(tools, tools->parser);
}
