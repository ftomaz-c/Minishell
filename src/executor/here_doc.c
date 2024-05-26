/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/26 23:04:45 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Gets the status of a terminated process and updates the global status.
 * 
 * @param status Pointer to the status variable containing the termination
 * status of the process.
 */
void	get_status(int *status)
{
	if (WIFSIGNALED(*status))
	{
		g_sig = WTERMSIG(*status);
		if (g_sig == SIGINT)
			global_status()->nbr = 130;
		else if (g_sig == SIGQUIT)
			global_status()->nbr = 131;
	}
	else if (WIFEXITED(*status))
		global_status()->nbr = WEXITSTATUS(*status);
}

/**
 * @brief Waits for a here-document process to finish and handles its status.
 * 
 * @param tools Pointer to the tools structure containing necessary data.
 * @param status Pointer to the status variable containing the termination
 * status of the process.
 * @param pid Process ID of the here-document process.
 */
void	status_heredoc(t_tools *tools, int *status, int pid)
{
	waitpid(pid, status, 0);
	get_status(status);
	if (global_status()->nbr)
		free_and_exit(tools, global_status()->nbr);
	dup2(tools->fd[0], STDIN_FILENO);
	close(tools->fd[0]);
	handle_child_sigaction();
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
 */

void	get_here_doc(t_tools *tools, int fd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (global_status()->nbr == 130)
		{
			free(line);
			free_and_exit(tools, global_status()->nbr);
		}
		if (!line)
		{
			eof_sig_msg(tools, line, delimiter);
			free_and_exit(tools, EXIT_SUCCESS);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
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
void	here_doc(t_tools *tools, char *delimiter)
{
	pid_t	pid;
	int		status;

	if (pipe(tools->fd) == -1)
	{
		perror("Error creating pipes");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error in child process");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(tools->fd[0]);
		global_status()->nbr = 0;
		get_here_doc(tools, tools->fd, delimiter);
	}
	else
	{
		close(tools->fd[1]);
		status_heredoc (tools, &status, pid);
	}
}
