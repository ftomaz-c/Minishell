#include "../../includes/minishell.h"

void	remove_whoami(char **env, char *user)
{
	pid_t	pid;
	int		status;
	char	*argv[3];

	argv[0] = "rm";
	argv[1] = "whoami.txt";
	argv[2] = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		execve("/usr/bin/rm", argv, env);
	else
		waitpid(pid, &status, 0);
	free(user);
}

void	get_whoami(char **env)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*argv[2];

	argv[0] = "whoami";
	argv[1] = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		fd = open("whoami.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		execve("/usr/bin/whoami", argv, env);
	}
	else
		waitpid(pid, &status, 0);
}

char	*get_source_home_var(t_tools *tools, char *str)
{
	//char	*line;
	char	*home;
	char	*user;
	int		fd;

	get_whoami(tools->env);
	fd = open("whoami.txt", O_RDONLY);
	user = get_next_line(fd);
	close(fd);
	user[ft_strlen(user) - 1] = '\0';
	home = ft_strjoin(str, user);
	remove_whoami(tools->env, user);
	close(fd);
	return (home);
}
