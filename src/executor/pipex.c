/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 17:08:09 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Duplicates a file descriptor and closes the original.
 * 
 * This function duplicates the file descriptor `dup_fd` 
 * onto the file descriptor `dup_fd2`
 * and closes the original file descriptor `close_fd`.
 * 
 * @param close_fd The file descriptor to close.
 * @param dup_fd The file descriptor to duplicate.
 * @param dup_fd2 The file descriptor onto which `dup_fd` is duplicated.
 * @return None.
 */
void	pipex_dup_and_close(int close_fd, int dup_fd, int dup_fd2)
{
	if (close_fd != -1)
		close (close_fd);
	dup2(dup_fd, dup_fd2);
	close(dup_fd);
}

/**
 * @brief Executes a piped command.
 * 
 * This function handles execution of commands connected by pipes.
 * 
 * @param parser The parser containing command information.
 * @param tools The tools struct containing necessary information.
 */
void	minishell_pipex(t_tools *tools, t_parser *parser, int *index)
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
			if (parser->next)
				pipex_dup_and_close(pipe_fd[0], pipe_fd[1], STDOUT_FILENO);
			execute_cmd(tools, parser);
		}
	}
	else
	{
		pipex_dup_and_close(pipe_fd[1], pipe_fd[0], STDIN_FILENO);
		tools->pids[*index] = pid;
	}
}
