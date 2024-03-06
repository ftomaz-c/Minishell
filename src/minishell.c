#include "../includes/minishell.h"

void	minishell(t_tools *tools)
{
	char	*line;

	//line = prompt_line(&tools);
	line = readline(".minishell: ");
	add_history_file(line, ".minishell_history");
	if (check_unclosed_quotes(line))
	{
		if (!lex_line(line, tools))
		{
			free(line);
			free_lexer(&tools->lexer);
			return ;
		}
		//print_lexer(tools);
		if (!parser(tools))
			return ;
		//print_parser(tools);
		if (tools->lexer)
			free_lexer(&tools->lexer);
		if (tools->parser)
		{
			executor(tools);
			free_parser(&tools->parser);
		}
	}
	else
		ft_putstr_fd("Error: input with unclosed quotes\n", STDERR_FILENO);
	free(line);
}
