/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/27 15:34:40 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/**
 * @brief Sends a specified signal to multiple processes.
 * 
 * This function iterates through the process IDs stored in tools->pids
 * and sends the specified signal to each process.
 * 
 * @param tools   A pointer to the tools structure containing process IDs.
 * @param num_pids The number of process IDs to which the signal should be sent.
 * @param signal  The signal to be sent to the processes.
 */
void	broadcast_signal(t_tools *tools, int num_pids, int signal)
{
	int			i;

	i = 0;
	while (i < num_pids)
	{
		kill (tools->pids[i], signal);
		i++;
	}
}

/**
 * @brief Handles non-interactive mode for the shell.
 * 
 * This function checks if the shell is in non-interactive mode and if the
 * exit flag is not set. If these conditions are met, it prints an error message
 * indicating the line number.
 * 
 * @param tools A pointer to the tools structure.
 */
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
void	exec_err(t_tools *tools, int err, char *str)
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
}

/**
 * @brief Waits for a child process to change state and updates the global 
 * status.
 * 
 * This function waits for the child process with the specified PID to change
 * state.
 * It updates the global_status variable with the exit status of the child
 * process if it exited normally.
 * 
 * @param tools  A pointer to the tools structure.
 * @param pid    Process ID of the child process to wait for.
 * @param status Pointer to an integer to store the exit status of the child
 * process.
 */
void	wait_status(t_tools *tools, int pid, int *status)
{
	int	i;

	waitpid(pid, status, 0);
	get_status(status);
	i = 3;
	while (i < 1024)
		close(i++);
	if (global_status()->nbr == 130)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (global_status()->nbr == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	dup2(tools->original_stdin, STDIN_FILENO);
	dup2(tools->original_stdout, STDOUT_FILENO);
}
