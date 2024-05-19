/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:20:49 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Removes the file "whoami.txt" created by the `get_whoami` function.
 * 
 * This function removes the file "whoami.txt" from the filesystem.
 * 
 * @param env The array of environment variables.
 */
void	remove_whoami(char **env)
{
	pid_t	pid;
	int		status;
	char	*argv[3];

	argv[0] = "rm";
	argv[1] = "whoami.txt";
	argv[2] = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		execve("/usr/bin/rm", argv, env);
	else
		waitpid(pid, &status, 0);
}

/**
 * @brief Executes the `whoami` command and stores the output in a file.
 * 
 * This function executes the `whoami` command using execve and redirects
 * its output to a file named "whoami.txt".
 * 
 * @param env The array of environment variables.
 */
void	get_whoami(char **env)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*argv[2];

	argv[0] = "whoami";
	argv[1] = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		fd = open("whoami.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		execve("/usr/bin/whoami", argv, env);
	}
	else
		waitpid(pid, &status, 0);
}

/**
 * @brief Concatenates the given string with the username
 * stored in the tools structure.
 * 
 * This function concatenates the given string with the username
 * stored in the tools structure,
 * typically representing the HOME variable.
 * 
 * @param tools A pointer to the tools structure containing user information.
 * @param str The string to concatenate with the username.
 * @return A pointer to the concatenated string.
 */
char	*get_source_home_var(t_tools *tools, char *str)
{
	char	*home;

	home = ft_strjoin(str, tools->user);
	return (home);
}

/**
 * @brief Retrieves the username by executing the `whoami` command
 * and reading the output from a file.
 * 
 * This function executes the `whoami` command to retrieve
 * the current username,
 * reads the output from the file "whoami.txt", and returns the username.
 * 
 * @param tools A pointer to the tools structure containing
 * environment variables.
 * @return A pointer to a string containing the username.
 */
char	*get_source_user_var(t_tools *tools)
{
	char	*user;
	int		fd;

	get_whoami(tools->env);
	fd = open("whoami.txt", O_RDONLY);
	user = get_next_line(fd);
	close(fd);
	user[ft_strlen(user) - 1] = '\0';
	remove_whoami(tools->env);
	return (user);
}
