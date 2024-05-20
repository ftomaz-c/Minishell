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

void	get_here_doc(t_tools *tools)
{
	char	*line;

	handle_pipex_heredoc(here_doc_sig);
	close(here_doc_struct()->fd[0]);
	while (1)
	{
		line = readline("> ");
		if (g_status == 133)
			close_sig_exit(tools, here_doc_struct()->fd[1], EXIT_FAILURE);
		if (!line)
			eof_sig_msg_exit(tools, line);
		if (ft_strncmp(line, here_doc_struct()->heredoc_limiter,
				ft_strlen(here_doc_struct()->heredoc_limiter)) == 0)
		{
			free(line);
			close(here_doc_struct()->fd[1]);
			exit (EXIT_SUCCESS);
		}
		write(here_doc_struct()->fd[1], line, ft_strlen(line));
		write(here_doc_struct()->fd[1], "\n", 1);
		free(line);
	}
	handle_pipex_heredoc(sig_pipex_handler);
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

	status = 0;
	handle_pipex_sigaction(SIG_DFL);
	dup2(tools->original_stdin, STDIN_FILENO);
	if (pipe(here_doc_struct()->fd) == -1)
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
		get_here_doc(tools);
	else
	{
		close(here_doc_struct()->fd[1]);
		wait_status(tools, pid, &status);
	}
}
