/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 12:10:32 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Sets up stdin redirection based on the parser's
 * stdin flag and file name.
 * 
 * This function handles stdin redirection for a parsed command.
 * If the parser's stdin flag indicates '<' (LESS), it opens the
 * specified file for reading,
 * performs stdin redirection, and closes the file descriptor.
 * If the stdin flag indicates '<<' (LESS_LESS), it initiates a here document.
 * 
 * @param tools Pointer to the tools structure containing environment
 * and execution context.
 * @param parser Pointer to the parser containing stdin redirection
 * information.
 * @param fd The file descriptor associated with stdin redirection.
 */
void	set_stdin(t_tools *tools, t_parser *parser, int fd)
{
	int	fd_infile;

	(void)tools;
	if (parser->stdin_flag == LESS)
	{
		fd_infile = open (parser->stdin_file_name, O_RDONLY);
		if (fd_infile < 0)
		{
			std_err(errno, parser->stdin_file_name);
			if (errno == 2 && parser->next)
			{
				global_status()->nbr = 127;
				return ;
			}
			else
			{
				global_status()->nbr = EXIT_FAILURE;
				exit (global_status()->nbr);
			}
		}
		dup2(fd_infile, fd);
		close(fd_infile);
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
 */

t_lexer	*set_input(t_tools *tools, t_parser *parser, t_lexer *redirection,
			int fd)
{
	t_lexer		*current;

	current = redirection;
	current = current->next;
	if (parser->stdin_flag == LESS_LESS)
	{
		handle_heredoc_sigaction();
		current = current->next;
		parser->delimiter = current->words;
		dup2(tools->original_stdout, STDOUT_FILENO);
		dup2(tools->original_stdin, STDIN_FILENO);
		here_doc(tools, parser->delimiter);
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
	if (fd_outfile != fd && fd_outfile != STDOUT_FILENO)
		close(fd_outfile);
	return ;
}

/**
 * @brief Sets up stdout redirection based on the parser's stdout
 * flag and the redirection tokens.
 * 
 * This function determines the type of stdout redirection based on
 * the parser's stdout flag and the redirection tokens.
 * If the flag indicates '>>' (GREAT_GREAT), it sets the stdout file name
 * from the next token and performs stdout redirection.
 * If the flag indicates '>' (GREAT), it also sets the stdout file name
 * and performs stdout redirection.
 * 
 * @param parser Pointer to the parser containing redirection information.
 * @param redirection Pointer to the current token in the
 * redirection token stream.
 * @param fd The file descriptor associated with the redirection.
 * @return Pointer to the next token in the redirection token stream
 * after processing stdout redirection.
 */
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

/**
 * @brief Handles input and output redirection based on the parsed command.
 * 
 * This function processes input and output redirection for a parsed command.
 * It iterates through the redirection tokens in the parser's redirection list,
 * sets up the appropriate file descriptors, and performs
 * stdin and stdout redirection
 * based on the redirection tokens and parser flags.
 * 
 * @param tools Pointer to the tools structure containing
 * environment and execution context.
 * @param parser Pointer to the parser containing redirection information.
 */
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
