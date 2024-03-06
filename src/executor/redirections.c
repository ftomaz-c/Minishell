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

void	set_stdin_flag(t_parser *parser, t_lexer *redirections)
{
	t_lexer	*current;

	current = redirections;
	if (current->token == '<')
	{
		parser->stdout_flag = 0;
		if (current->next && current->next->token == '<')
			parser->stdin_flag = LESS_LESS;
		else if (current->next->words)
			parser->stdin_flag = LESS;
	}
	return ;
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

void	set_stdout_flag(t_parser *parser, t_lexer *redirections)
{
	t_lexer	*current;

	current = redirections;
	if (current->token == '>')
	{
		if (current->token == '<' && current->next->token == '>')
			current = current->next;
		if (current->next && current->next->token == '>')
			parser->stdout_flag = GREAT_GREAT;
		else
			parser->stdout_flag = GREAT;
	}
	return ;
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

t_lexer	*set_input(t_parser *parser, t_lexer *redirection, int fd)
{
	t_lexer	*current;

	current = redirection;
	current = current->next;
	if (parser->stdin_flag == LESS_LESS)
	{
		current = current->next;
		parser->heredoc_limiter = current->words;
	}
	else if (parser->stdin_flag == LESS)
		parser->stdin_file_name = current->words;
	set_stdin(parser, fd);
	return (current);
}

t_lexer	*set_output(t_parser *parser, t_lexer *redirection, int fd)
{
	t_lexer *current;

	current = redirection;
	current = current->next;
	if (parser->stdout_flag == GREAT_GREAT)
	{
		current = current->next;
		parser->stdout_file_name = current->words;
	}
	else if (parser->stdout_flag == GREAT)
		parser->stdout_file_name = current->words;
	set_stdout(parser, fd);
	return (current);
}

int	get_digits_token(t_lexer *current)
{
	char	*nbr;
	int		size;
	int		i;
	int		token;

	i = 0;
	size = 2;
	nbr = ft_calloc(size, sizeof(char));
	if (!nbr)
		return (0);
	nbr[i] = current->token;
	while (ft_isdigit(current->next->token))
	{
		i++;
		current = current->next;
		nbr[i] = current->token;
		size++;
		nbr = ft_realloc(nbr, size * sizeof(char), (size - 1) * sizeof(char));
		if (!nbr)
			return (0);
		nbr[size - 1] = '\0';
	}
	token = ft_atoi(nbr);
	free(nbr);
	return (token);
}

int	set_fd(t_lexer *current)
{
	int		fd;

	if (ft_isdigit(current->token))
		fd = get_digits_token(current);
	else if (current->token == '<')
		fd = STDIN_FILENO;
	else if (current->token == '>')
		fd = STDOUT_FILENO;
	return (fd);
}

void	redirection(t_parser *parser)
{
	t_lexer	*current;
	int		fd;

	current = parser->redirections;
	while (current)
	{
		fd = set_fd(current);
		while (ft_isdigit(current->token))
			current = current->next;
		if (current->token == '<')
		{
			set_stdin_flag(parser, current);
			current = set_input(parser, current, fd);
		}
		else if (current->token == '>')
		{
			set_stdout_flag(parser, current);
			current = set_output(parser, current, fd);
		}
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

void	std_err(int	err, char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (err == 2)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	else if (err == 13)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (err == 21)
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	g_status = EXIT_FAILURE;
	exit (g_status);
}

void	set_stdin(t_parser *parser, int fd)
{
	int	fd_infile;

	if (parser->stdin_flag == LESS)
	{
		fd_infile = open (parser->stdin_file_name, O_RDONLY);
		if (fd_infile < 0)
		{
			std_err(errno, parser->stdin_file_name);
			if (errno == 2 && parser->next)
			{
				g_status = 127;
				return ;
			}
			else
			{
				g_status = EXIT_FAILURE;
				exit (g_status);
			}
		}
		dup2(fd_infile, fd);
	}
	else if (parser->stdin_flag == LESS_LESS)
		here_doc(parser->heredoc_limiter, parser->original_stdout);
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

void	set_stdout(t_parser *parser, int fd)
{
	int	fd_outfile;

	if (parser->stdout_flag == GREAT)
	{
		fd_outfile = open(parser->stdout_file_name, O_CREAT | O_RDWR
				|O_TRUNC, 0644);
		if (fd_outfile < 0)
			std_err(errno, parser->stdout_file_name);
		dup2(fd_outfile, fd);
	}
	else if (parser->stdout_flag == GREAT_GREAT)
	{
		fd_outfile = open(parser->stdout_file_name, O_CREAT | O_RDWR
				| O_APPEND, 0644);		
		if (fd_outfile < 0)
			std_err(errno, parser->stdout_file_name);
		dup2(fd_outfile, fd);
	}
	return ;
}
