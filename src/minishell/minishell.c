#include "../../includes/minishell.h"

void	minishell(t_tools *tools, char *line)
{
	tools->nprompts++;
	add_history_file(tools, line, ".minishell_history");
	if (check_unclosed_quotes(line))
	{
		if (!lexer(line, tools))
		{
			free_lexer(&tools->lexer);
			return ;
		}
		//print_lexer(tools);
		if (!parser(tools))
			return ;
		if (tools->lexer)
			free_lexer(&tools->lexer);
		//print_parser(tools);
		if (tools->parser)
		{
			executor(tools);
			free_parser(&tools->parser);
		}
	}
	else
		ft_putstr_fd("minishell: input with unclosed quotes\n", STDERR_FILENO);
}

void	non_interactive_mode(t_tools *tools, char *line)
{
	int		n;
	int		i;
	char	**lines;

	n = 0;
	lines = ft_calloc(sizeof(char **), 1024);
	tools->nint_mode = 1;
	line = get_next_line(0);
	while (line)
	{
		lines[n] = ft_strdup(ft_strtrim(line, "\n"));
		n++;
		free(line);
		line = get_next_line(0);
	}
	i = 0;
	while (i < n)
	{
		minishell(tools, lines[i]);
		free(lines[i]);
		i++;
	}
	free(lines);
	tools->exit = 1;
}

void	interactive_mode(t_tools *tools, char *line)
{
	line = readline(".minishell: ");
	if (!line)
	{
		tools->exit = 1;
		ft_putstr_fd("exit\n", STDIN_FILENO);
		return ;
	}
	minishell(tools, line);
	free(line);
}
