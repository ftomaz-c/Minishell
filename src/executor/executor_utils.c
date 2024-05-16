/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/16 13:50:04 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

char	**basic_env(void)
{
	char	**b_env;

	b_env = calloc (sizeof(char *), 2);
	b_env[0] = ft_strdup("PATH=/bin:/usr/bin");
	return (b_env);
}

void	free_and_exit(t_tools *tools)
{
	free_parser(&tools->parser);
	free_tools(tools);
	exit(g_status);
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

void	exec_err(t_tools *tools, int err, char *str, char *value)
{
	nint_mode(tools);
	if (err == 1)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_status = 127;
	}
	else if (err == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_status = 127;
	}
	else if (err == 8)
		g_status = 0;
	else if (err == 13)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_status = 130;
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
 * */

// void delay(int milliseconds) {
//     // Get the current time in milliseconds
//     long long start_time = (long long)time(NULL) * 1000;
//     long long end_time = start_time + milliseconds;
	
//     // Loop until the specified time has elapsed
//     while ((long long)time(NULL) * 1000 < end_time);
// }


void	wait_status(int pid, int *status)
{
	(void)pid;

	waitpid(-1, status, 0);
	if (WIFEXITED(*status))
		g_status = WEXITSTATUS(*status);
}
