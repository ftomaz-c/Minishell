/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/27 12:29:16 by crebelo-         ###   ########.fr       */
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
	char	*tmp;
	int		i;

	i = 0;
	if (!get_var_from_env(envp, "PATH"))
	{
		if (!tools->empty_env)
		{
			exec_err(tools, 1, cmd_args[0]);
			return ;
		}
	}
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
	exec_err(tools, errno, cmd_args[0]);
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
void	execute_cmd(t_tools *tools, t_parser *parser, int index)
{
	if (parser->builtin && (parser->builtin == cmd_echo
			|| parser->builtin == cmd_env || parser->builtin == cmd_cd
			|| parser->builtin == cmd_pwd || parser->builtin == cmd_export
			|| parser->builtin == cmd_unset || parser->builtin == cmd_exit
			|| parser->builtin == cmd_history))
	{
		broadcast_signal(tools, index, SIGSTOP);
		parser->builtin(tools, parser);
		broadcast_signal(tools, index, SIGCONT);
		free_and_exit(tools, global_status()->nbr);
	}
	else if (!parser->builtin)
	{
		exec_path(tools, parser->str, tools->env);
		free_and_exit(tools, global_status()->nbr);
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
void	set_and_execute(t_tools *tools, t_parser *parser)
{
	int	index;
	int	i;
	int	status;

	tools->pids = ft_calloc(sizeof(int), tools->pipes + 1);
	if (!tools->pids)
		return ;
	index = 0;
	status = 0;
	while (parser)
	{
		if (parser->redirections != NULL)
			redirection(tools, parser, &index);
		minishell_pipex(tools, parser, &index);
		parser = parser->next;
		index++;
	}
	i = 0;
	while (i < tools->pipes + 1)
	{
		waitpid (tools->pids[i++], &status, 0);
		get_status(&status);
	}
}

/**
 * @brief Executes simple commands and builtins if no pipes or redirections are
 * present.
 * 
 * This function checks if there are no pipes and no redirections in the command.
 * If the command is a valid simple command or a builtin command, it executes
 * the command.
 * 
 * @param tools  Pointer to the tools struct containing necessary information.
 * @param parser Pointer to the parser struct containing the command information.
 * 
 * @return Returns 1 upon successful execution of a simple command or builtin, 0
 * otherwise.
 */
int	simple_exec_and_buitlins(t_tools *tools, t_parser *parser)
{
	if (!tools->pipes && parser->str[0] && !tools->parser->nb_redirections)
	{
		if (ft_strncmp("./", parser->str[0], 2) == 0)
		{
			if (is_valid(parser) > 0)
			{
				execute_simple_cmd(tools, parser);
				return (1);
			}
		}
		if (parser->str[0] && (parser->str[0][0] == '/'
			|| (ft_strncmp("./", parser->str[0], 2) == 0)) && !parser->str[1])
			parser->builtin = cmd_cd;
		if (parser->builtin && (parser->builtin == cmd_echo
				|| parser->builtin == cmd_env || parser->builtin == cmd_cd
				|| parser->builtin == cmd_pwd || parser->builtin == cmd_export
				|| parser->builtin == cmd_unset || parser->builtin == cmd_exit
				|| parser->builtin == cmd_history))
		{
			global_status()->nbr = parser->builtin(tools, parser);
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Executes the parsed command.
 * 
 * This function forks a child process and executes each parsed command
 * sequentially.
 * If a command is followed by a pipe ('|'), it pipes the output of the current
 * command
 * to the input of the next command.
 * 
 * @param tools The tools struct containing parser and other necessary
 * information.
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
	if (simple_exec_and_buitlins(tools, parser))
		return (global_status()->nbr);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		set_and_execute(tools, parser);
		free_and_exit(tools, global_status()->nbr);
	}
	else
		wait_status(tools, pid, &status);
	return (global_status()->nbr);
}
