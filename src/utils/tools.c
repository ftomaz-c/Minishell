#include "../../includes/minishell.h"

/**
 * @brief Retrieves the value of a variable from the environment.
 * 
 * This function searches the environment variables
 * for a specific variable
 * and returns its value.
 * 
 * @param envp The array of environment variables.
 * @param var The name of the variable to retrieve.
 * 
 * @return A pointer to the value of the variable if found,
 * or NULL if not found or on error.
 * 
 * @note Assumes envp is a valid array of environment variables.
 * 
 * @see get_env
 * 
 * @warning Make sure to free the memory allocated for the returned string.
 * 
 * @example
 * 
 * ```
 * char *value = get_var_from_env(envp, "PATH=");
 * if (value != NULL) {
 *     printf("PATH: %s\n", value);
 *     free(value);
 * }
 * ```
 */

char *get_var_from_env(char **env, char *var)
{
	int		index;
	char	*value;

	index = 0;
	if (!env || !var)
		return (NULL);
	while (env[index])
	{
		if (compare_var_to_env(env[index], var))
			break ;
		index++;
	}
	if (env[index])
		value = ft_substr(env[index], ft_strlen(var) + 1, ft_strlen(env[index]) + 1);
	else
		value = NULL;
	return (value);
}

/**
 * @brief Copies the environment variables into a new array.
 * 
 * This function creates a copy of the environment variables
 * and stores them
 * in a new dynamically allocated array.
 * 
 * @param envp The array of environment variables.
 * 
 * @return A pointer to the new array of environment variables,
 * or NULL on error.
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
 * char **env = get_env(envp);
 * if (env != NULL) {
 *     // Use env...
 *     free_env(env);
 * }
 * ```
 */

char	**get_env(char **envp)
{
	char	**env;
	int		count;
	int		index;

	count = 0;
	while (envp[count])
		count++;
	env = ft_calloc(sizeof(char *), count + 1);
	if (env == NULL)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		env[index] = ft_strdup(envp[index]);
		if (env[index] == NULL)
			return (NULL);
		index++;
	}
	return (env);
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

char	**get_path(char **env)
{
	char	*path_from_envp;
	char	**path_list;

	path_from_envp = get_var_from_env(env, "PATH");
	path_list = ft_split(path_from_envp, ":");
	free(path_from_envp);
	if (!path_list)
		return (NULL);
	return (path_list);
}

/**
 * @brief Configures the tools structure with environment information.
 * 
 * This function configures the tools structure with environment information,
 * including environment variables, the PATH variable,
 * current working directory,
 * and previous working directory.
 * 
 * @param tools A pointer to the tools structure to be configured.
 * @param envp The array of environment variables.
 * 
 * @return 1 on success, 0 on failure.
 * 
 * @note The tools structure must be properly initialized before calling
 * this function.
 * 
 * @see free_tools
 * 
 * @warning Make sure to check the return value for failure.
 * 
 * @example
 * 
 * ```
 * t_tools tools;
 * if (config_tools(&tools, envp)) {
 *     // Use tools...
 * } else {
 *     printf("Failed to configure tools\n");
 * }
 * ```
 */

int	config_tools(t_tools *tools, char **envp)
{
	if (!tools)
		return (0);
	tools->env = get_env(envp);
	tools->path = get_path(tools->env);
	if (tools->path == NULL)
		return (0);
	tools->pwd = get_var_from_env(tools->env, "PWD");
	if (tools->pwd == NULL)
		return (0);
	tools->oldpwd = get_var_from_env(tools->env, "OLDPWD");
	if (tools->oldpwd == NULL)
		return (0);
	tools->home = get_var_from_env(tools->env, "HOME");
	if (tools->home == NULL)
		return (0);
	tools->user = get_var_from_env(tools->env, "USER");
	if (tools->user == NULL)
		return (0);
	tools->name = get_var_from_env(tools->env, "NAME");
	if (tools->name == NULL)
		return (0);
	tools->pipes = 0;
	tools->parser = NULL;
	tools->exit = 0;
	return (1);
}
