#include "../../includes/executor.h"

char	*set_stdin_flag(t_parser *parser)
{
	if (parser->redirections->token == '<')
	{
		if (parser->redirections->next->token == '<')
		{
			parser->stdin_flag = LESS_LESS;
			return ("<<");
		}
		else
		{
			parser->stdin_flag = LESS;
			return ("<");
		}
	}
	return (NULL);
}

char	*set_stdout_flag(t_parser *parser)
{
	if (parser->redirections->token == '>')
	{
		if (parser->redirections->next->token == '>')
		{
			parser->stdout_flag = GREAT_GREAT;
			return (">>");
		}
		else
		{
			parser->stdout_flag = GREAT;
			return (">");
		}
	}
	return (NULL);
}

void	redirection(t_parser *parser)
{
	char	*stdin_flag;
	char	*stdout_flag;

	while (parser->redirections)
	{
		stdin_flag = set_stdin_flag(parser);
		stdout_flag = set_stdout_flag(parser);
		parser->redirections = parser->redirections->next;
		if (stdin_flag != NULL && ft_strncmp(stdin_flag, "<<", 2) == 0)
		{
			parser->redirections = parser->redirections->next;
			parser->heredoc_limiter = parser->redirections->words;
		}
		else if (stdin_flag != NULL && ft_strncmp(stdin_flag, "<", 1) == 0)
			parser->stdin_file_name = parser->redirections->words;
		if (stdout_flag != NULL && ft_strncmp(stdout_flag, ">>", 2) == 0)
		{
			parser->redirections = parser->redirections->next;
			parser->stdout_file_name = parser->redirections->words;
		}
		else if (stdout_flag != NULL && ft_strncmp(stdout_flag, ">", 1) == 0)
			parser->stdout_file_name = parser->redirections->words;
		parser->redirections = parser->redirections->next;
	}
}

void	set_stdin(t_parser *parser)
{
	int fd_infile;
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (parser->stdin_flag == LESS)
	{
		fd_infile = open (parser->stdin_file_name, O_RDONLY);
		if (fd_infile < 0)
			exit (EXIT_FAILURE);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else if (parser->stdin_flag == LESS_LESS)
		here_doc(parser->heredoc_limiter, original_stdout);
	else
		return ;
}

void	set_stdout(t_parser *parser)
{
	int	fd_outfile;

	if (parser->stdout_flag == GREAT)
	{
		fd_outfile = open(parser->stdout_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd_outfile < 0)
			exit (EXIT_FAILURE);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else if (parser->stdout_flag == GREAT_GREAT)
	{
		fd_outfile = open(parser->stdout_file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd_outfile < 0)
			exit (EXIT_FAILURE);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else
		return ;
}