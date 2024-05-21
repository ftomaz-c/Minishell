/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:30:55 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	set_stdin(t_tools *tools, t_parser *parser, int fd)
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
		close(fd_infile);
	}
	else if (parser->stdin_flag == LESS_LESS)
		here_doc(tools);
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

t_lexer	*set_input(t_tools *tools, t_parser *parser, t_lexer *redirection,
	int fd)
{
	t_lexer	*current;

	current = redirection;
	current = current->next;
	if (parser->stdin_flag == LESS_LESS)
	{
		current = current->next;
		parser->limiter = current->words;
		dup2(tools->original_stdin, STDIN_FILENO);
	}
	else if (parser->stdin_flag == LESS)
		parser->stdin_file_name = current->words;
	set_stdin(tools, parser, fd);
	return (current);
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

	fd_outfile = 0;
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
	if (parser->fd_err)
		dup2(fd_outfile, parser->fd_err);
	if (fd_outfile)
		close(fd_outfile);
	return ;
}

t_lexer	*set_output(t_parser *parser, t_lexer *redirection, int fd)
{
	t_lexer	*current;

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

void	redirection(t_tools *tools, t_parser *parser)
{
	t_lexer	*current;
	int		fd;

	current = parser->redirections;
	while (current)
	{
		fd = set_fd(current, parser);
		if (current->token == '&')
			current = current->next;
		while (ft_isdigit(current->token))
			current = current->next;
		if (current->token == '<')
		{
			set_stdin_flag(parser, current);
			current = set_input(tools, parser, current, fd);
		}
		if (current->token == '>')
		{
			set_stdout_flag(parser, current);
			current = set_output(parser, current, fd);
		}
		current = current->next;
	}
}
