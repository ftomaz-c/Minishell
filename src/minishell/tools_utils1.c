#include "../../includes/minishell.h"

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
 * 
 * @note Assumes the tools structure is properly initialized.
 * 
 * @see config_tools
 * 
 * @warning Make sure to call this function to avoid memory leaks
 * after using the tools structure.
 * 
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
 * 
 * @note Memory allocated for the returned array and its elements
 * must be freed by the caller.
 * 
 * @see config_tools
 * 
 * @warning The caller is responsible for freeing the memory allocated
 * for the returned array and its elements.
 * 
 * @example
 * 
 * ```
 * char **path_list = get_path(env);
 * if (path_list != NULL) {
 *     // Use path_list...
 *     free_path_list(path_list);
 * }
 * ```
 */

char	**get_path(t_tools *tools, char **env)
{
	char	*path_from_envp;
	char	**path_list;

	path_from_envp = get_var_from_env(env, "PATH");
	if (!path_from_envp)
	{
		path_from_envp = ft_strdup("PATH=/bin:/usr/bin");
		export_variable_to_env(tools, path_from_envp);
	}
	path_list = ft_split(path_from_envp, ":");
	free(path_from_envp);
	if (!path_list)
		return (NULL);
	return (path_list);
}
