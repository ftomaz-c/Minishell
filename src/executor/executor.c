#include "../../includes/executor.h"

void	wait_status(int pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		global_status = WEXITSTATUS(*status);
}

void	execute_cmd(t_tools *tools, t_parser *parser)
{
	if (exec_builtins(parser) || parser->builtin == echo 
		|| parser->builtin == env)
	{
		parser->builtin(tools, parser);
		if (parser->next)
			exit (global_status);
	}
	else
		exec_path(tools->path, parser->str, tools->env);
	return ;
}

/**
 * @brief Sets up the executor based on parser data.
 * 
 * This function configures redirections and sets up standard input and output.
 * If redirections are present, it calls the redirection function.
 * 
 * @param parser The parser containing command and redirection information.
 * 
 * @note This function assumes that the parser is properly initialized.
 * 
 * @see redirection
 */

void	set_and_exec(t_tools *tools, t_parser *parser)
{
	if (parser->redirections != NULL)
		redirection(parser);
	set_stdin(parser);
	set_stdout(parser);
	if (parser->next)
		minishell_pipex(tools, parser);
	else
		execute_cmd(tools, parser);
}

/**
 * @brief Executes the parsed command.
 * 
 * This function forks a child process and executes each parsed command sequentially.
 * If a command is followed by a pipe ('|'), it pipes the output of the current command
 * to the input of the next command.
 * 
 * @param tools The tools struct containing parser and other necessary information.
 * 
 * @return Returns 1 upon successful execution.
 * 
 * @warning This function assumes that the tools struct is properly initialized.
 */

int	executor(t_tools *tools)
{
	t_parser	*parser;
	pid_t		pid;
	int 		status;

	parser = tools->parser;
	parser->original_stdout = dup(STDOUT_FILENO);
	if (exec_builtins(tools->parser) && !tools->pipes)
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
		exit(global_status);
	}
	else
		wait_status(pid, &status);
	return (status);
}

