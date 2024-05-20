#include "../../includes/executor.h"

void	fd_exit(int exit_code, int original_stdout)
{
	close(original_stdout);
	exit(exit_code);
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
 * 
 * @note This function assumes that the input is properly terminated.
 * 
 * @see get_next_line
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
 * 
 * @warning This function assumes that pipe creation and forking succeed.
 * 
 * @see get_here_doc
 */

void	here_doc(t_tools *tools)
{
	pid_t	pid;
	int		status;

	handle_sigaction(ignore_sig_pipex);
	dup2(tools->original_stdin, STDIN_FILENO);
	if (pipe(tools->parser->fd) == -1)
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
		close(tools->parser->fd[0]);
		get_here_doc(tools, tools->parser->fd);
	}
	else
	{
		close(tools->parser->fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			g_status = 130;
		else if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		if (g_status == 130)
			free_and_exit(tools, g_status);
		dup2(tools->parser->fd[0], STDIN_FILENO);
		close(tools->parser->fd[0]);
		handle_sigaction(sig_pipex_handler);
	}
}
