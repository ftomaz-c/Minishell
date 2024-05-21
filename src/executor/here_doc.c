/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:15:47 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Closes the original stdout file descriptor and exits the
 * program with the specified exit code.
 * 
 * This function closes the original stdout file descriptor and then
 * exits the program with the given exit code.
 * 
 * @param exit_code The exit code to be returned by the program.
 * @param original_stdout The original file descriptor for stdout.
 * @return None.
 */
void	fd_exit(int exit_code, int original_stdout)
{
	close(original_stdout);
	exit(exit_code);
}

/**
 * @brief Closes the file descriptor for a here document and
 * exits with the specified status.
 * 
 * This function frees memory associated with the parser and tools,
 * closes the file descriptor for the here document,
 * and exits with the specified status.
 * 
 * @param tools A pointer to the tools structure.
 * @param fd The file descriptor for the here document.
 * @param status The exit status for the program.
 * @return None.
 */

void	get_here_doc(t_tools *tools, int fd[2])
{
	char	*line;

	handle_sigaction(here_doc_sig);
	g_status = 0;
	while (1)
	{
		line = readline("> ");
		if (g_status == 130)
		{
			free(line);
			free_and_exit(tools, g_status);
		}
		if (!line)
			eof_sig_msg_exit(tools, line);
		if (ft_strncmp(line, tools->parser->limiter,
				ft_strlen(tools->parser->limiter)) == 0)
		{
			free(line);
			free_and_exit(tools, EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

/**
 * @brief Implements here documents functionality.
 * 
 * This function creates a child process to handle here documents input.
 * 
 * @param limiter The delimiter indicating the end of input.
 * @param original_stdout The original file descriptor for stdout.
 */
void	here_doc(t_tools *tools)
{
	pid_t	pid;
	int		status;

	handle_sigaction(ignore_sig_pipex);
	if (pipe(tools->parser->fd) == -1)
	{
		perror("Error creating pipes");
		exit (EXIT_FAILURE);
	}
	handle_sigaction(sig_pipex_handler);
	pid = fork();
	if (pid == -1)
	{
		perror("Error in child process");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(tools->parser->fd[0]);
		get_here_doc(tools, tools->parser->fd);
	}
	else
	{
		close(tools->parser->fd[1]);
		wait_status (tools, pid, &status, 1);
	}
}
