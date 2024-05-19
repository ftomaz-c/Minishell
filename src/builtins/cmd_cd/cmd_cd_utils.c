/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:12:30 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"
/**
 * @brief Updates the environment variables PWD and OLDPWD 
 * with the current and previous working directories.
 * 
 * This function updates the environment variables PWD and 
 * OLDPWD with the current and previous working directories, respectively.
 * 
 * @param tools Pointer to the tools struct containing necessary information.
 */
void	update_env_vars(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (strncmp("PWD", tools->env[i], 3) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("PWD=", tools->pwd);
		}
		else if (strncmp("OLDPWD", tools->env[i], 6) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("OLDPWD=", tools->oldpwd);
		}
		i++;
	}
}

/**
 * @brief Prints error messages related to the cd command.
 * 
 * This function prints error messages related to the cd command
 * to the standard error stream.
 * 
 * @param err The error code.
 * @param str Additional string to be printed.
 * @param root Flag indicating if the root directory is involved.
 */
void	cd_err(int err, char *str, char root)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!(root == '/'))
		ft_putstr_fd("cd: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (err == 1)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (err == 2 || err == 3)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (err == 4)
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	else if (err == 13)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (err == 20)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else if (err == 0 || err == 25)
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else if (err == 36)
		ft_putstr_fd(": File name too long\n", STDERR_FILENO);
	g_status = EXIT_FAILURE;
}

/**
 * @brief Handles changing to the previous directory
 * specified by an absolute path.
 * 
 * This function changes to the previous directory specified
 * by an absolute path
 * and updates the environment variables accordingly.
 * 
 * @param tools A pointer to the tools structure.
 * @return Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	cd_handle_slash_path(t_tools *tools)
{
	if (chdir(tools->oldpwd) == 0)
	{
		printf("%s\n", tools->oldpwd);
		free(tools->pwd);
		tools->pwd = ft_strdup(tools->oldpwd);
		free(tools->oldpwd);
		tools->oldpwd = get_var_from_env(tools->env, "PWD");
		return (EXIT_SUCCESS);
	}
	else
		cd_err(2, tools->oldpwd, 0);
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles changing to the directory specified by a 
 * relative path containing '.'.
 * 
 * This function changes to the directory specified by a relative 
 * path containing '.'
 * and updates the environment variables accordingly.
 * 
 * @param tools A pointer to the tools structure.
 * @return Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	cd_handle_dot_path(t_tools *tools)
{
	char	*tmp;

	if (chdir(tools->pwd) == 0)
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent directories", STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		tmp = ft_strdup(tools->pwd);
		free(tools->pwd);
		tools->pwd = ft_strjoin(tmp, "/.");
		free(tmp);
		return (EXIT_SUCCESS);
	}
}
