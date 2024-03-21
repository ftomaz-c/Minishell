#include "../includes/minishell.h"

void	minishell(t_tools *tools, char *line)
{
	add_history_file(line, ".minishell_history");
	if (check_unclosed_quotes(line))
	{
		if (!lexer(line, tools))
		{
			free_lexer(&tools->lexer);
			return ;
		}
		// print_lexer(tools);
		if (!parser(tools))
			return ;
		// print_parser(tools);
		if (tools->lexer)
			free_lexer(&tools->lexer);
		if (tools->parser)
		{
			executor(tools);
			free_parser(&tools->parser);
		}
	}
	else
		ft_putstr_fd("minishell: input with unclosed quotes\n", STDERR_FILENO);
}
