#include "../../includes/executor.h"

/**
 * @brief Sets the stdin flag based on redirection token.
 * 
 * This function sets the stdin flag in the parser struct based on the redirection token.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @return Returns the redirection symbol ("<" or "<<") if stdin redirection is detected, otherwise NULL.
 */

char	*set_stdin_flag(t_parser *parser)
{
	if (parser->redirections->token == '<')
	{
		if (parser->redirections->next && parser->redirections->next->token == '<')
		{
			parser->stdin_flag = LESS_LESS;
			return ("<<");
		}
		else if (parser->redirections->next->token != '<')
		{
			parser->stdin_flag = LESS;
			return ("<");
		}
	}
	return (NULL);
}

/**
 * @brief Sets the stdout flag based on redirection token.
 * 
 * This function sets the stdout flag in the parser struct based on the redirection token.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @return Returns the redirection symbol (">" or ">>") if stdout redirection is detected, otherwise NULL.
 */

char	*set_stdout_flag(t_parser *parser)
{
	if (parser->redirections->token == '>')
	{
		if (parser->redirections->next && parser->redirections->next->token == '>')
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

/**
 * @brief Handles redirections for a parsed command.
 * 
 * This function parses the redirections in a command and sets up stdin and stdout accordingly.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @note This function assumes that the parser is properly initialized.
 * 
 * @see set_stdin_flag, set_stdout_flag
 */

		/*if (!parser->redirections->next)
		{
			printf("bash: syntax error near unexpected token `newline'");
			exit (EXIT_FAILURE)
		}*/

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

/**
 * @brief Sets up standard input based on parser data.
 * 
 * This function redirects standard input for a command if stdin redirection is detected.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @note This function assumes that the parser is properly initialized.
 */

void	set_stdin(t_parser *parser)
{
	int fd_infile;
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (parser->stdin_flag == LESS)
	{
		fd_infile = open (parser->stdin_file_name, O_RDONLY);
		if (fd_infile < 0)
		{
			printf("bash: there: No such file or directory\n");
			exit (EXIT_FAILURE);
		}
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else if (parser->stdin_flag == LESS_LESS)
		here_doc(parser->heredoc_limiter, original_stdout);
	else
		return ;
}

/**
 * @brief Sets up standard output based on parser data.
 * 
 * This function redirects standard output for a command if stdout redirection is detected.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @note This function assumes that the parser is properly initialized.
 */

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