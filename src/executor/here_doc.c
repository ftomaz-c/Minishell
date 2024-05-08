#include "../../includes/executor.h"

void	sig_pipex_handler(int sig)
{
	(void)sig;
	exit(g_status);
}

void	handle_pipex_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_pipex_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (SIGINT, &sa, NULL);
}

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

void	get_here_doc(char *limiter, int fd[2], int original_stdout)
{
	char	*line;

	close(fd[0]);
	ft_putstr_fd("> ", original_stdout);
	line = NULL;
	while (1)
	{
		line = get_next_line(1);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			fd_exit(EXIT_SUCCESS, original_stdout);
		}
		write(fd[1], line, ft_strlen(line));
		ft_putstr_fd("> ", original_stdout);
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

void	here_doc(char *limiter, int original_stdout)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("Error creating pipes");
		fd_exit(EXIT_FAILURE, original_stdout);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error in child process");
		fd_exit(EXIT_FAILURE, original_stdout);
	}
	if (pid == 0)
	{
		get_here_doc(limiter, fd, original_stdout);
		pipex_dup_and_close(-1, fd[1], original_stdout);
	}
	else
	{
		pipex_dup_and_close(fd[1], fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
