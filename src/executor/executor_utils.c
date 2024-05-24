/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 17:19:54 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	broadcast_signal(t_tools *tools, int num_pids, int signal)
{
	int	i;

	i = 0;
	while (i < num_pids)
	{
		if (kill (tools->pids[i], signal) < 0)
			perror("Failed to broadcast signal");
		i++;
	}
}

/**
 * @brief Creates a basic environment for the shell.
 * 
 * This function creates a basic environment for the shell containing
 * only the PATH variable.
 * 
 * @return A pointer to the array of environment variables.
 */
char	**basic_env(void)
{
	char	**b_env;

	b_env = calloc (sizeof(char *), 3);
	b_env[0] = ft_strdup("PATH=/bin:/usr/bin");
	b_env[1] = ft_strdup("_=/bin/env");
	return (b_env);
}

void	nint_mode(t_tools *tools)
{
	if (tools->nint_mode && !tools->exit)
	{
		ft_putstr_fd("minishell: line ", STDERR_FILENO);
		ft_putnbr_fd(tools->line_count, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

/**
 * @brief Handles execution errors by printing error messages
 * and updating the global status.
 * 
 * This function handles execution errors by printing the
 * corresponding error message,
 * updating the global status, and freeing any allocated memory.
 * 
 * @param tools A pointer to the tools structure.
 * @param err The error code.
 * @param str The string representing the command or file causing the error.
 * @param value A pointer to the value to be freed, if applicable.
 * @return None.
 */
void	exec_err(t_tools *tools, int err, char *str, char *value)
{
	nint_mode(tools);
	if (err == 1)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		global_status()->nbr = 127;
	}
	else if (err == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		global_status()->nbr = 127;
	}
	else if (err == 8)
		global_status()->nbr = 0;
	else if (err == 13)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		global_status()->nbr = 130;
	}
	if (value)
		free(value);
}

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
 */
void	wait_status(t_tools *tools, int pid, int *status)
{
	int	i;

	waitpid(pid, status, 0);
	get_status(status);
	i = 3;
	while (i < 1024)
		close(i++);
	dup2(tools->original_stdin, STDIN_FILENO);
	dup2(tools->original_stdout, STDOUT_FILENO);
}
