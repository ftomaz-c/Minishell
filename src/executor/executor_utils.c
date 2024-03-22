#include "../../includes/executor.h"

void	exec_err(int err, char *str, char *value)
{
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
		if (value)
			free(value);
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

