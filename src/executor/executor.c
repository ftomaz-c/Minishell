#include "../../includes/executor.h"

/**
 * @brief Waits for a child process to change state and 
 * updates the global status.
 * 
 * This function waits for the child process with the specified 
 * PID to change state.
 * It updates the global_status variable with the exit status
 *  of the child process if it exited normally.
 * 
 * @param pid    Process ID of the child process to wait for.
 * @param status Pointer to an integer to store the exit 
 * status of the child process.
 * 
 * @note This function assumes the process with the given PID 
 * is a child process.
 *       It assumes the status pointer is valid and points to 
 * a writable memory location.
 * 
 * @warning Behavior is undefined if status is NULL.
 * 
 * @see waitpid, WIFEXITED, WEXITSTATUS
 * 
 * @example
 * ```
 * // Example usage of wait_status function
 * int pid = fork(); // Fork a child process
 * if (pid == 0) {
 *     // Child process code
 * } else {
 *     int status;
 *     wait_status(pid, &status); // Wait for the child 
 * process to change state
 *     // Use the status variable to handle the exit status
 *  of the child process
 * }
 * ```
 */

void	wait_status(int pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		g_status = WEXITSTATUS(*status);
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
 * 
 * @note This function assumes the validity of the tools
 *  and parser structs.
 * 
 * @see exec_path, global_status
 * 
 * @example
 * ```
 * // Example usage of execute_cmd function
 * t_tools *tools = initialize_tools(); // Initialize
 *  tools struct
 * t_parser *parser = initialize_parser(); // Initialize
 *  parser struct
 * execute_cmd(tools, parser); // Execute the command
 * specified in the parser
 * ```
 */

void	execute_cmd(t_tools *tools, t_parser *parser)
{
	if (parser->builtin && (exec_builtins(tools) || parser->builtin == echo
			|| parser->builtin == env))
	{
		parser->builtin(tools, parser);
		if (parser->next)
			exit (g_status);
	}
	else
		exec_path(tools->path, parser->str, tools->env);
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
 * 
 * @note This function assumes that the parser is properly initialized.
 * 
 * @see redirection
 */

void	set_and_exec(t_tools *tools, t_parser *parser)
{
	if (parser->redirections != NULL)
		redirection(parser);
	if (parser->next)
		minishell_pipex(tools, parser);
	else
		execute_cmd(tools, parser);
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
 * 
 * @warning This function assumes that the tools
 * struct is properly initialized.
 */

int	executor(t_tools *tools)
{
	t_parser	*parser;
	pid_t		pid;
	int			status;

	parser = tools->parser;
	parser->original_stdout = dup(STDOUT_FILENO);
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
		exit(g_status);
	}
	else
		wait_status(pid, &status);
	return (status);
}
