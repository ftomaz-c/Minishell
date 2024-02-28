#include "../../includes/executor.h"

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

void	get_here_doc(char *limiter, int fd, int original_stdout)
{
	char	*line;

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
			exit(EXIT_SUCCESS);
		}
		write(fd, line, ft_strlen(line));
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
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error in child process");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		get_here_doc(limiter, fd[1], original_stdout);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
