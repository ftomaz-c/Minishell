#include "../../includes/builtins.h"

/**
 * @brief Check if a variable with a similar path exists in the environment.
 * 
 * This function checks if a variable with a similar path exists in the environment.
 * 
 * @param env Pointer to the array of environment variables.
 * @param var Pointer to the variable to check.
 * 
 * @return Returns 1 if a similar variable exists, otherwise returns 0.
 * 
 * @see find_char_position(), ft_strncmp()
 */
int check_var_path(char **env, char *var)
{
	int		index;
	int		equal_pos;
	int		equal_pos_var;

	index = 0;
	equal_pos_var = find_char_position(var, '=');
	while (var && env[index])
	{
		equal_pos = find_char_position(env[index], '=');
		if (equal_pos < equal_pos_var)
			equal_pos = equal_pos_var;
		if (!ft_strncmp(env[index], var, equal_pos))
			return (1);
		index++;
	}
	return (0);
}

/**
 * @brief Copy variable value.
 * 
 * This function copies the variable value from the input string starting from the specified position.
 * 
 * @param var_path Pointer to the destination string where the value will be copied.
 * @param str Input string containing the variable and its value.
 * @param start Starting position from where to copy the value.
 * 
 * @note This function assumes that the destination string is large enough to hold the copied value.
 */
void	copy_var_value(char *var_path, char *str, int start)
{
	int	i;

	i = 0;
	if (start >= (int)ft_strlen(str))
	{
		var_path = NULL;
		return ;
	}
	while (start < (int)ft_strlen(str))
	{
		var_path[i] = str[start];
		i++;
		start++;
	}
}

/**
 * @brief Get the new variable value.
 * 
 * This function extracts the new variable value from the input string.
 * 
 * @param var_value Pointer to the destination string where the value will be stored.
 * @param str Input string containing the variable and its value.
 * 
 * @note This function allocates memory for the new value string.
 */
void	get_new_var_value(char **var_value, char *str)
{
	int		start;
	int		i;

	i = find_char_position(str, '=') + 1;
	if (i >= (int)ft_strlen(str))
	{
		*var_value = NULL;
		return ;
	}
	start = i;
	while (str[i] && i < (int)ft_strlen(str))
		i++;
	*var_value = ft_calloc(sizeof(char *), (ft_strlen(str) - start) + 1);
	if (!var_value)
		return ;
	copy_var_value(*var_value, str, start);
}

/**
 * @brief Substitute the environment variable value.
 * 
 * This function substitutes the value of the environment variable with the new value.
 * 
 * @param tools Pointer to the tools structure containing environment variables.
 * @param var_path Pointer to the variable path.
 * @param str Input string containing the variable and its new value.
 * 
 * @note This function frees the memory allocated for the old value and path.
 */
void	substitute_env_var_value(t_tools *tools, char *var_path, char *str)
{
	int		i;
	char	*var_value;
	int		equal_pos;

	i = 0;
	get_new_var_value(&var_value, str);
	while (tools->env[i])
	{
		equal_pos = find_char_position(tools->env[i], '=');
		if (var_path && strncmp(tools->env[i], var_path , equal_pos) == 0)
		{
			free(tools->env[i]);
			if (!var_value)
				tools->env[i] = ft_strdup(var_path);
			else
				tools->env[i] = ft_strjoin(var_path, var_value);
			break ;
		}
		i++;
	}
	free(var_value);
	free(var_path);
}
