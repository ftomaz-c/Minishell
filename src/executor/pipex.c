#include "../../includes/executor.h"

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
			close(pipe_fd[1]);
			execute_cmd(tools, parser);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
	// close(pipe_fd[0]);
}
