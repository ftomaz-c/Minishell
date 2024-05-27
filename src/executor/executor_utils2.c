/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:46:35 by ftomazc           #+#    #+#             */
/*   Updated: 2024/05/27 23:18:13 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	child_waitpid(t_tools *tools, int *status)
{
	int	i;

	i = 0;
	while (i < tools->pipes + 1)
	{
		waitpid (tools->pids[i++], status, 0);
		get_status(status);
	}
}

/**
 * @brief Executes a simple command by forking a child process and executing the
 * command.
 * 
 * @param tools Pointer to the tools structure containing environment variables
 * and other necessary data.
 * @param parser Pointer to the parser structure containing the command string
 * to be executed.
 */
void	execute_simple_cmd(t_tools *tools, t_parser *parser, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror("minishell: ");
	else if (pid == 0)
		exec_path(tools, parser->str, env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			global_status()->nbr = WEXITSTATUS(status);
	}
}

/**
 * @brief Checks if the command in the parser is a valid file and determines its
 * type.
 * 
 * @param parser Pointer to the parser structure containing the command string
 * to be checked.
 * 
 * @returns Returns 1 if the file is executable, 0 if it's a directory, 2 if
 * it's a regular file, -1 if it doesn't exist, and -2 for any other cases.
 */
int	is_valid(t_parser *parser)
{
	struct stat	file_stat;

	if (stat(parser->str[0], &file_stat) != 0)
		return (-1);
	if (S_ISDIR(file_stat.st_mode))
		return (0);
	if (file_stat.st_mode & S_IXUSR)
		return (1);
	if (S_ISREG(file_stat.st_mode))
		return (2);
	return (-2);
}

/**
 * @brief Determines if the command is executable by checking the PATH
 * environment variable.
 * 
 * @param tools Pointer to the tools structure containing environment variables
 * and other necessary data.
 * @param cmd_args Array of command arguments to be checked.
 * @param envp Array of environment variables.
 * 
 * @returns int Returns 1 if the command is executable, otherwise returns 0.
 */
int	is_executable(t_tools *tools, char **cmd_args, char **envp)
{
	char	*value;

	value = get_var_from_env(envp, "PATH");
	if (!value)
	{
		if (!tools->empty_env)
		{
			exec_err(tools, 1, cmd_args[0]);
			return (0);
		}
	}
	free(value);
	return (1);
}
