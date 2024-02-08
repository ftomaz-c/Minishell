#include "../includes/minishell.h"

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
	int	i;

	i = 0;
	if (tools->env)
	{
		while (tools->env[i])
		{
			free(tools->env[i]);
			i++;
		}
		free(tools->env);
	}
	i = 0;
	if (tools->path)
	{
		while (tools->path[i])
		{
			free(tools->path[i]);
			i++;
		}
		free(tools->path);
	}
	free(tools->pwd);
	free(tools->oldpwd);
	ft_memset(tools, 0, sizeof(t_tools));
}

/**
 * @brief Retrieves the value of a variable from the environment.
 * 
 * This function searches the environment variables
 * for a specific variable and returns its value.
 * 
 * @param var The name of the variable to retrieve, in the form "NAME=". 
 * 
 * @return A pointer to the value of the variable if found,
 * or NULL if not found or on error.
 * 
 * @note This function relies on the system's getenv function to retrieve
 * the value of the variable. It assumes that var is provided in the format
 * "NAME=", where NAME is the name of the environment variable.
 * 
 * @warning The returned string is allocated in memory managed by the system.
 * The caller should ensure to free the memory allocated for the returned string
 * using the appropriate deallocation function, such as free(), to prevent memory leaks.
 * 
 * @example
 * 
 * ```
 * char *value = get_var_from_env("PATH=");
 * if (value != NULL) {
 *     printf("PATH: %s\n", value);
 *     free(value); // Ensure to free the memory allocated for the returned string.
 * }
 * ```
 * 
 * @see getenv
 */

char	*get_var_from_env(char *var)
{
	char	*value;
	char	*env;

	if (!var)
		return (NULL);
	env = getenv(var);
	if (env)
		value = ft_substr(env, 0, ft_strlen(env));
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

char	**get_path(void)
{
	char	*path_from_envp;
	char	**path_list;

	path_from_envp = get_var_from_env("PATH");
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
	if (tools->env == NULL)
		return (0);
	tools->path = get_path();
	if (tools->path == NULL)
		return (0);
	tools->pwd = get_var_from_env("PWD");
	if (tools->pwd == NULL)
		return (0);
	tools->oldpwd = get_var_from_env("OLDPWD");
	if (tools->oldpwd == NULL)
		return (0);
	return (1);
}
