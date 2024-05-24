/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 19:31:23 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_tools *tools, int status)
{
	int	i;

	i = 3;
	while (i < 1024)
		close(i++);
	free_parser(&tools->parser);
	free_tools(tools);
	exit (status);
}

/**
 * @brief Retrieves the current working directory (PWD).
 * 
 * This function retrieves the current working directory (PWD)
 * either from the environment variables
 * or using the getcwd function. If the PWD is not found in the environment
 * variables, it is obtained
 * using getcwd, and then the PWD environment variable is updated accordingly.
 * 
 * @param tools A pointer to the tools structure containing environment
 * variables.
 * @param env The array of environment variables.
 * @return A pointer to a string containing the current
 * working directory (PWD).
 */
char	*get_pwd(t_tools *tools, char **env)
{
	char	buffer[1024];
	char	*pwd;
	char	*tmp;

	pwd = get_var_from_env(env, "PWD");
	if (!pwd)
	{
		pwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
		tmp = ft_strjoin("PWD=", pwd);
		export_variable_to_env(tools, tmp);
		free(tmp);
	}
	return (pwd);
}

/**
 * @brief Compares a variable to an environment variable.
 * 
 * This function compares a variable to an environment variable.
 * It checks if the variable matches
 * the format "VAR=value" where "VAR" is the variable
 * name and "value" is its value.
 * 
 * @param env The environment variable to compare.
 * @param var The variable to compare.
 * @return 1 if the variable matches the environment variable, 0 otherwise.
 */
int	compare_var_to_env(char *env, char *var)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] && var[i])
	{
		if (env[i] == var[i])
			i++;
		else
			return (0);
	}
	if (var[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

/**
 * @brief Frees the memory allocated for the tools structure.
 * 
 * This function frees the memory allocated for the tools
 * structure, including its
 * environment variables, path list, current working directory,
 * and previous working directory.
 * 
 * @param tools A pointer to the tools structure.
 * 
 * @return None. 
 */
void	free_tools(t_tools *tools)
{
	if (!tools)
		return ;
	if (tools && tools->env)
		free_list(tools->env);
	if (tools && tools->path)
		free_list(tools->path);
	if (tools && tools->pwd)
		free(tools->pwd);
	if (tools && tools->oldpwd)
		free(tools->oldpwd);
	if (tools && tools->home)
		free(tools->home);
	if (tools && tools->user)
		free(tools->user);
	if (tools && tools->name)
		free(tools->name);
	if (tools->pids)
		free(tools->pids);
	if (tools->nint_mode)
		free_list(tools->lines);
}

/**
 * @brief Retrieves the value of the PATH variable from the
 * environment and splits it into individual paths.
 * 
 * This function retrieves the value of the PATH variable from the environment,
 * splits it into individual paths separated by colons, and
 * stores them in an array.
 * 
 * @param env The array of environment variables.
 * 
 * @return A pointer to the array of path strings, or NULL on error.
 */
char	**get_path(t_tools *tools, char **env)
{
	char	*path_from_envp;
	char	**path_list;

	path_from_envp = get_var_from_env(env, "PATH");
	if (!path_from_envp)
	{
		path_from_envp = ft_strdup("PATH=/bin:/usr/bin");
		export_variable_to_env(tools, "_=/usr/bin/env");
		tools->empty_env = 1;
	}
	path_list = ft_split(path_from_envp, ":");
	free(path_from_envp);
	if (!path_list)
		return (NULL);
	return (path_list);
}
