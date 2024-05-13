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

void	get_here_doc(t_tools *tools, char *limiter, int fd[2], int stdout)
{
	char	*line;

	close(fd[0]);
	ft_putstr_fd("> ", stdout);
	line = NULL;
	while (1)
	{
		line = get_next_line(1);
		if (!line && g_status != 414)
		{
			ft_putstr_fd("\n", stdout);
			printf("minishell: warning: here-document at line %d delimited by\
				end-of-file (wanted `%s')\n", tools->nprompts, limiter);
			close_heredoc_exit(tools, fd[1], EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close_heredoc_exit(tools, fd[1], EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		ft_putstr_fd("> ", stdout);
		free(line);
	}
}

void	signal_exit(t_tools *tools, int fd[2])
{
	if (g_status == 414)
	{
		close(fd[0]);
		close(fd[1]);
		free_and_exit(tools);
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

void	here_doc(t_tools *tools, char *limiter, int stdout)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
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
		get_here_doc(tools, limiter, fd, stdout);
		pipex_dup_and_close(-1, fd[1], stdout);
	}
	else
	{
		pipex_dup_and_close(fd[1], fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	signal_exit(tools, fd);
}
