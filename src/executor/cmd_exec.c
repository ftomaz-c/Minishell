#include "../../includes/executor.h"

void	exec_err(int err, char *str)
{
	if (err == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (err == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	g_status = 127;
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
 * 
 * @note This function assumes the validity of the parser struct.
 *       It assumes the parser's builtin function pointer
 * accurately represents the command.
 * 
 * @warning Behavior is undefined if parser is NULL.
 * 
 * @see cd, pwd, export, unset, mini_exit, mini_history
 * 
 * @example
 * ```
 * // Example usage of exec_builtins function
 * t_parser *parser = initialize_parser(); // Initialize
 *  parser struct
 * int is_builtin = exec_builtins(parser); // Check if parser
 *  contains a builtin command
 * // is_builtin will be 1 if parser contains a builtin 
 * command, otherwise 0.
 * ```
 */

int	exec_builtins(t_parser *parser)
{
	if (parser->str[0][0] == '/' && !parser->str[1])
	{
		parser->builtin = cd;
		return (1);
	}
	if (parser && (parser->builtin == cd || parser->builtin == pwd
			|| parser->builtin == export || parser->builtin == unset
			|| parser->builtin == mini_exit || parser->builtin == mini_history))
		return (1);
	return (0);
}

/**
 * @brief Executes a command with the provided path.
 * 
 * This function attempts to execute a command using the specified path list.
 * 
 * @param path_list The list of paths to search for the command.
 * @param cmd_args The command arguments.
 * @param envp The environment variables.
 * 
 * @note This function assumes that the command and path 
 * list are properly initialized.
 */

void	exec_path(char **path_list, char **cmd_args, char **envp)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	if (!get_var_from_env(envp, "PATH"))
		exec_err(1, cmd_args[0]);
	else
	{
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
		exec_err(2, cmd_args[0]);
	}
	exit(g_status);
}

/**
 * @brief Executes a piped command.
 * 
 * This function handles execution of commands connected by pipes.
 * 
 * @param parser The parser containing command information.
 * @param tools The tools struct containing necessary information.
 * 
 * @warning This function assumes that pipe creation and forking succeed.
 * 
 * @see exec_path
 */

void	minishell_pipex(t_tools *tools, t_parser *parser)
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
			execute_cmd(tools, parser);
		else
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			execute_cmd(tools, parser);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
