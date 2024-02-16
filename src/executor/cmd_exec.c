#include "../../includes/executor.h"

void	exec_path(char **path_list, char **cmd_args, char **envp)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		i++;
	}
	if (cmd_args)
		execve(cmd_args[0], cmd_args, envp);
	printf("%s: command not found\n", cmd_args[0]);
}

void	minishell_pipex(t_parser *parser, t_tools *tools)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
		exit (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit (EXIT_FAILURE);
	else if (pid == 0)
	{
		if (parser->stdout_flag)
			exec_path(tools->path, parser->str, tools->env);
		else
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			exec_path(tools->path, parser->str, tools->env);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}