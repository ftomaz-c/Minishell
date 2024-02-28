#include "../../includes/executor.h"

/**
 * @brief Sets the stdin flag based on redirection token.
 * 
 * This function sets the stdin flag in the parser struct
 *  based on the redirection token.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @return Returns the redirection symbol ("<" or "<<") if 
 * stdin redirection is detected, otherwise NULL.
 */

t_lexer	*set_stdin_flag(t_parser *parser, t_lexer *redirections)
{
	t_lexer	*current;

	current = redirections;
	if (current->token == '<')
	{
		if (current->next && current->next->token == '<')
			parser->stdin_flag = LESS_LESS;
		else if (current->next->words)
			parser->stdin_flag = LESS;
	}
	return (current);
}

/**
 * @brief Sets the stdout flag based on redirection token.
 * 
 * This function sets the stdout flag in the parser struct
 *  based on the redirection token.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @return Returns the redirection symbol (">" or ">>") if stdout 
 * redirection is detected, otherwise NULL.
 */

t_lexer	*set_stdout_flag(t_parser *parser, t_lexer *redirections)
{
	t_lexer	*current;

	current = redirections;
	if (current->token == '>' || (current->next && current->next->token == '>'))
	{
		if (current->token == '<' && current->next->token == '>')
			current = current->next;
		else if (current->token == '>' && current->next->token == '<')
		{
			printf("bash: syntax error near unexpected token `<\n");
			g_status = 2;
			free_parser(&parser);
			exit (g_status);
		}
		if (current->next && current->next->token == '>')
			parser->stdout_flag = GREAT_GREAT;
		else
			parser->stdout_flag = GREAT;
	}
	return (current);
}

/**
 * @brief Handles redirections for a parsed command.
 * 
 * This function parses the redirections in a command and sets 
 * up stdin and stdout accordingly.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @note This function assumes that the parser is properly initialized.
 * 
 * @see set_stdin_flag, set_stdout_flag
 */

void	redirection(t_parser *parser)
{
	t_lexer	*current;

	current = parser->redirections;
	while (current)
	{
		current = set_stdin_flag(parser, current);
		current = set_stdout_flag(parser, current);
		current = current->next;
		if (parser->stdin_flag != 0 && parser->stdin_flag == LESS_LESS)
		{
			current = current->next;
			parser->heredoc_limiter = current->words;
		}
		else if (parser->stdin_flag != 0 && parser->stdin_flag == LESS)
			parser->stdin_file_name = current->words;
		if (parser->stdout_flag != 0 && parser->stdout_flag == GREAT_GREAT)
		{
			current = current->next;
			parser->stdout_file_name = current->words;
		}
		else if (parser->stdout_flag != 0 && parser->stdout_flag == GREAT)
			parser->stdout_file_name = current->words;
		current = current->next;
	}
}

/**
 * @brief Sets up standard input based on parser data.
 * 
 * This function redirects standard input for a command 
 * if stdin redirection is detected.
 * 
 * @param parser The parser containing redirection information.
 * 
 * @note This function assumes that the parser is properly initialized.
 */

void	set_stdin(t_parser *parser)
{
	int	fd_infile;

	if (parser->stdin_flag == LESS)
	{
		fd_infile = open (parser->stdin_file_name, O_RDONLY);
		if (fd_infile < 0)
		{
			printf("bash: %s: No such file or directory\n",
				parser->stdin_file_name);
			g_status = EXIT_FAILURE;
			return ;
		}
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	else if (parser->stdin_flag == LESS_LESS)
		here_doc(parser->heredoc_limiter, parser->original_stdout);
	else
		return ;
}

/**
 * @brief Sets up standard output based on parser data.
 * 
 * This function redirects standard output for a command 
 * if stdout redirection is detected.
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
		fd_outfile = open(parser->stdout_file_name, O_CREAT | O_RDWR
				|O_TRUNC, 0644);
		if (fd_outfile < 0)
			exit (EXIT_FAILURE);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else if (parser->stdout_flag == GREAT_GREAT)
	{
		fd_outfile = open(parser->stdout_file_name, O_CREAT | O_RDWR
				| O_APPEND, 0644);
		if (fd_outfile < 0)
			exit (EXIT_FAILURE);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else
		return ;
}
