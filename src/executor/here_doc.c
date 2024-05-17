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

void	close_heredoc_exit(t_tools *tools, int fd, int status)
{
	free_parser(&tools->parser);
	free_tools(tools);
	close(fd);
	exit(status);
}

void	get_here_doc(t_tools *tools)
{
	char	*line;
	int		here_nprompt;

	here_nprompt = tools->nprompts;
	free_parser(&tools->parser);
	free_tools(tools);
	close(here_doc_struct()->fd[0]);
	line = NULL;
	while (g_status != 133)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
			ft_putnbr_fd(here_nprompt, 2);
			ft_putstr_fd("delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(here_doc_struct()->heredoc_limiter, 2);
			ft_putstr_fd("')\n", 2);
			free(here_doc_struct()->heredoc_limiter);
			close(here_doc_struct()->fd[1]);
			free(line);
			exit (EXIT_FAILURE);
		}
		if (ft_strncmp(line, here_doc_struct()->heredoc_limiter,
				ft_strlen(here_doc_struct()->heredoc_limiter)) == 0)
		{
			free(line);
			exit (EXIT_SUCCESS);
		}
		write(here_doc_struct()->fd[1], line, ft_strlen(line));
		write(here_doc_struct()->fd[1], "\n", 1);
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
	{
		handle_pipex_heredoc(here_doc_sig);
		get_here_doc(tools);
		pipex_dup_and_close(-1, here_doc_struct()->fd[1], STDOUT_FILENO);
	}
	else
	{
		pipex_dup_and_close(here_doc_struct()->fd[1], here_doc_struct()->fd[0],
			STDIN_FILENO);
		wait_status(pid, &status);
	}
}
