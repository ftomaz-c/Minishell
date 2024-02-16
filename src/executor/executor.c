#include "../../includes/executor.h"

void	set_executor(t_parser *parser)
{
	if (parser->redirections != NULL)
		redirection(parser);
	set_stdin(parser);
	set_stdout(parser);
}

int	executor(t_tools *tools)
{
	t_parser	*parser;
	pid_t		pid;
	int 		status;

	parser = tools->parser;
	if (!parser)
		return (1);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		while (parser)
		{
			set_executor(parser);
			if (parser->next)
				minishell_pipex(parser, tools);
			else
				exec_path(tools->path, parser->str, tools->env);
			parser = parser->next;
		}
	}
	else
		waitpid(pid, &status, 0);
	return (1);
}
