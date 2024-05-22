/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/22 16:52:10 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Executes a command with the provided path.
 * 
 * This function attempts to execute a command using the specified path list.
 * 
 * @param path_list The list of paths to search for the command.
 * @param cmd_args The command arguments.
 * @param envp The environment variables.
 */
void	exec_path(t_tools *tools, char **cmd_args, char **envp)
{
	char	*cmd_path;
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	value = get_var_from_env(envp, "PATH");
	if (!value)
		exec_err(tools, 1, cmd_args[0], value);
	else
	{
		while (tools->path[i] && cmd_args[0] && cmd_args[0][0] != '.')
		{
			tmp = ft_strjoin(tools->path[i], "/");
			cmd_path = ft_strjoin(tmp, cmd_args[0]);
			free(tmp);
			execve(cmd_path, cmd_args, envp);
			free(cmd_path);
			i++;
		}
		if (cmd_args[0] && !tools->nint_mode)
			execve(cmd_args[0], cmd_args, envp);
		exec_err(tools, errno, cmd_args[0], value);
	}
}

/**
 * @brief Checks if the provided parser contains a 
 * builtin command.
 * 
 * This function checks if the provided parser struct 
 * contains a builtin command.
 * It compares the parser's builtin function pointer with
 * known builtin commands.
 * 
 * @param parser Pointer to the parser struct containing the 
 * command information.
 * 
 * @return 1 if the parser contains a builtin command, 0 otherwise.
 */
int	exec_builtins(t_tools *tools)
{
	t_parser	*parser;

	parser = tools->parser;
	if (parser->str[0] && parser->str[0][0] == '/' && !parser->str[1])
	{
		parser->builtin = cmd_cd;
		return (1);
	}
	if (parser->builtin && (parser->builtin == cmd_cd
			|| parser->builtin == cmd_pwd
			|| parser->builtin == cmd_export || parser->builtin == cmd_unset
			|| parser->builtin == cmd_exit || parser->builtin == cmd_history))
	{
		return (1);
	}
	return (0);
}

/**
 * @brief Executes a command based on its type (builtin or external).
 * 
 * This function executes a command based on whether it is 
 * a builtin command or an external command.
 * If the command is a builtin command (like echo or env),
 *  it executes it directly.
 * If the command is an external command, it executes it
 *  using exec_path function.
 * 
 * @param tools  Pointer to the tools struct containing
 *  necessary information.
 * @param parser Pointer to the parser struct containing
 * the command information.
 */
void	execute_cmd(t_tools *tools, t_parser *parser)
{
	char	*cmd_args[2];

	if (parser->builtin && (parser->builtin == cmd_env && parser->str[1]))
	{
		cmd_args[0] = parser->str[2];
		cmd_args[1] = NULL;
		exec_path(tools, cmd_args, basic_env());
		free_and_exit(tools, g_status);
	}
	if (parser->builtin && (exec_builtins(tools) || parser->builtin == cmd_echo
			|| parser->builtin == cmd_env))
	{
		parser->builtin(tools, parser);
		if (parser->next)
			free_and_exit(tools, g_status);
	}
	else
	{
		exec_path(tools, parser->str, tools->env);
		free_and_exit(tools, g_status);
	}
	return ;
}

/**
 * @brief Sets up the executor based on parser data.
 * 
 * This function configures redirections and sets up 
 * standard input and output.
 * If redirections are present, it calls the redirection function.
 * 
 * @param parser The parser containing command and 
 * redirection information.
 */
void	set_and_exec(t_tools *tools, t_parser *parser)
{
	if (parser->redirections != NULL)
		redirection(tools, parser);
	if (parser->next)
		minishell_pipex(tools, parser);
	else
		execute_cmd(tools, parser);
	waitpid(0, NULL, 0);
}

/**
 * @brief Executes the parsed command.
 * 
 * This function forks a child process and executes 
 * each parsed command sequentially.
 * If a command is followed by a pipe ('|'), it pipes 
 * the output of the current command
 * to the input of the next command.
 * 
 * @param tools The tools struct containing parser and
 * other necessary information.
 * 
 * @return Returns 1 upon successful execution.
 */
int	executor(t_tools *tools)
{
	t_parser	*parser;
	pid_t		pid;
	int			status;

	handle_child_sigaction();
	parser = tools->parser;
	status = 0;
	if (exec_builtins(tools) && !tools->pipes && parser->str[0])
		return (parser->builtin(tools, parser));
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		while (parser)
		{
			set_and_exec(tools, parser);
			parser = parser->next;
		}
		free_and_exit(tools, g_status);
	}
	else
		wait_status(tools, -1, &status, 0);
	return (status);
}
