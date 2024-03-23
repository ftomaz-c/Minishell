#include "../../includes/minishell.h"

void	remove_whoami(char **env, char *user)
{
	pid_t	pid;
	int		status;
	char	*argv[] = {"rm", "whoami.txt", NULL};

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
	char	*argv[] = {"whoami", NULL};

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

char	*get_home_from_etc_passwd(char *line)
{
	char	*home;
	int		i;
	int		j;
	int		colon;

	i = 0;
	j = 0;
	colon = 0;
	home = calloc(1024 , sizeof(char));
	if (!home)
		return (NULL);
	while (line[i])
	{
		if (line[i] == ':')
		{
			i++;
			colon++;
		}
		if (colon == 5)
			home[j++] = line[i];
		else if (colon > 5)
			break;
		i++;
	}
	return (home);
}

char	*get_source_home_var(t_tools *tools, char *str)
{
	char	*line;
	char	*home;
	char	*user;
	int		fd;

	get_whoami(tools->env);
	fd = open("whoami.txt", O_RDONLY);
	user = get_next_line(fd);
	close(fd);
	user[ft_strlen(user) - 1] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_putstr_fd("Error: Failed to open file\n", STDERR_FILENO);
	while (1)
	{
		line = get_next_line(fd);
		if (ft_strncmp(user, line, ft_strlen(user)) == 0)
			break ;
		free(line);
	}
	home = get_home_from_etc_passwd(line);
	remove_whoami(tools->env, user);
	close(fd);
	free(line);
	return (home);
}
