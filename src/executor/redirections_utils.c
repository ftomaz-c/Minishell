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
		if (current->token == '<' && current->next->token == '>')
			return ;
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
		parser->stdin_flag = 0;
		if (current->next && current->next->token == '>')
			parser->stdout_flag = GREAT_GREAT;
		else
			parser->stdout_flag = GREAT;
	}
	return ;
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

int	set_fd(t_lexer *current, t_parser *parser)
{
	int		fd;

	fd = 0;
	parser->fd_err = 0;
	if (ft_isdigit(current->token))
		fd = get_digits_token(current);
	else if (current->token == '&' && current->next->token == '>')
	{
		parser->fd_err = STDERR_FILENO;
		fd = STDOUT_FILENO;
	}
	else if (current->token == '<' && !current->next->token)
		fd = STDIN_FILENO;
	else if (current->token == '>')
		fd = STDOUT_FILENO;
	return (fd);
}

void	std_err(int err, char *str)
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
