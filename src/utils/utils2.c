#include "../../includes/utils.h"

/**
 * @brief Calculates the length of a string until newline character.
 * 
 * This function calculates the length of a string until it encounters
 * either a null terminator or a newline character.
 * 
 * @param s Pointer to the string.
 * 
 * @return Returns the length of the string until the newline character 
 * or null terminator.
 * 
 * @note This function assumes that `s` points to a valid null-terminated string.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char *str = "Hello\nWorld";
 * size_t length = ft_strlen_nl(str);
 * ```
 */
size_t	ft_strlen_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	return (i);
}

/**
 * @brief Constructs a file path by appending a file name 
 * to the user's home directory path.
 * 
 * This function constructs a file path by concatenating
 *  the user's home directory path
 * obtained from the HOME environment variable with
 *  the provided file name.
 * 
 * @param file_name The name of the file to append to
 * the home directory path.
 * 
 * @return A dynamically allocated string containing the 
 * constructed file path.
 *         The caller is responsible for freeing the memory 
 * allocated for the string.
 *         Returns NULL if memory allocation fails or if the
 *  HOME environment variable is not set.
 * 
 * @note The caller must free the memory allocated for the 
 * returned string after use to avoid memory leaks.
 * @note This function relies on the ft_strjoin function to concatenate strings.
 * @note Assumes that the HOME environment variable is set
 *  to the user's home directory path.
 * 
 * @warning If memory allocation fails or if the HOME
 *  environment variable is not set,
 *          this function returns NULL without modifying errno.
 * 
 * @see ft_strjoin
 * 
 * @example
 * 
 * ```
 * // Example usage of the function
 * char *file_path = get_file_path_from_home("example.txt");
 * if (file_path) {
 *     // Use the file_path
 *     printf("File path: %s\n", file_path);
 *     // Free the memory allocated for the file path when no longer needed
 *     free(file_path);
 * } else {
 *     // Handle error: unable to retrieve file path
 *     fprintf(stderr, "Error: Failed to retrieve file path.\n");
 * }
 * ```
 */
char	*get_file_path_from_home(char *home, char *file_name)
{
	char	*home_var;
	char	*tmp;

	home_var = ft_strjoin(home, "/");
	if (!home_var)
		return (NULL);
	tmp = ft_strjoin(home_var, file_name);
	if (!tmp)
		return (NULL);
	free(home_var);
	return (tmp);
}

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

char	*get_var_from_env(char **env, char *var)
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
		value = ft_substr(env[index], ft_strlen(var) + 1,
				ft_strlen(env[index]));
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
	if (!envp)
		return (NULL);
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
 * @brief Frees the memory allocated for a null-terminated array of strings.
 * 
 * This function frees the memory allocated for each string in the array 'list',
 * as well as the memory allocated for the array itself.
 * 
 * @param list Pointer to the array of strings to free.
 * 
 * @note This function assumes that 'list' is a null-terminated array of strings.
 * 
 * @warning The function does not perform input validation on 'list'.
 *          It may result in unexpected behavior if 'list' is NULL
 * or if any of its elements are NULL.
 * 
 * @example
 * ```
 * char *list[] = {"Hello", "world", NULL};
 * free_list(list);
 * // All memory allocated for the array 'list' and its strings will be freed
 * ```
 */

void	free_list(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
