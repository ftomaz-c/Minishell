#include "../../includes/executor.h"

void	get_here_doc(char *limiter, int fd, int original_stdout)
{
	char	*line;

	ft_putstr_fd("> ", original_stdout);
	while ((line = get_next_line(1)))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			exit (EXIT_SUCCESS);
		write(fd, line, ft_strlen(line));
		ft_putstr_fd("> ", original_stdout);
	}
}

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