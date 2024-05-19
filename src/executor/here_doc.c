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
void	close_heredoc_exit(t_tools *tools, int fd, int status)
{
	free_parser(&tools->parser);
	free_tools(tools);
	close(fd);
	exit(status);
}

/**
 * @brief Exits the program if the status is 901.
 * 
 * This function closes the file descriptors associated with the
 * pipe, frees memory, and exits the program
 * if the global status is 901.
 * 
 * @param tools A pointer to the tools structure.
 * @param fd An array of file descriptors associated with the pipe.
 * @return None.
 */
void	signal_exit(t_tools *tools, int fd[2])
{
	if (g_status == 901)
	{
		close(fd[0]);
		close(fd[1]);
		free_and_exit(tools);
	}
}

/**
 * @brief Reads input until a delimiter is encountered 
 * and writes it to a file descriptor.
 * 
 * This function reads input from stdin until the specified 
 *delimiter is encountered and
 * writes it to the provided file descriptor.
 * 
 * @param limiter The delimiter indicating the end of input.
 * @param fd The file descriptor to write the input to.
 * @param original_stdout The original file descriptor for stdout.
 */
void	get_here_doc(t_tools *tools, char *limiter, int fd[2], int stdout)
{
	char	*line;

	close(fd[0]);
	line = NULL;
	while (g_status != 901)
	{
		line = readline("> ");
		if (!line && g_status != 901)
		{
			printf("minishell: warning: here-document at line %d delimited by",
				tools->nprompts);
			printf("end-of-file (wanted `%s')\n", limiter);
			close_heredoc_exit(tools, fd[1], EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close_heredoc_exit(tools, fd[1], EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
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
void	here_doc(t_tools *tools, char *limiter, int stdout)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
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
		handle_sigaction(sig_pipex_handler);
		get_here_doc(tools, limiter, fd, stdout);
		signal_exit(tools, fd);
		pipex_dup_and_close(-1, fd[1], stdout);
	}
	else
	{
		signal_exit(tools, fd);
		pipex_dup_and_close(fd[1], fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	signal_exit(tools, fd);
}
