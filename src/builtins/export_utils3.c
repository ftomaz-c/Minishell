#include "../../includes/builtins.h"

/**
 * @brief Check if a character is alphabetic or an underscore.
 * 
 * This function checks if the input character is alphabetic (A-Z, a-z) or an underscore (_).
 * 
 * @param c Character to check.
 * 
 * @return Returns 1 if the character is alphabetic or an underscore, otherwise returns 0.
 */
int	ft_isalpha_plus_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

/**
 * @brief Find the position of a character in a string.
 * 
 * This function finds the position of the specified character in the input string.
 * 
 * @param str Input string to search.
 * @param c Character to find.
 * 
 * @return Returns the position of the character in the string, or the length of the string if the character is not found.
 */
int	find_char_position(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief Copy characters from a string to another string.
 * 
 * This function copies characters from the input string to the destination string.
 * 
 * @param var_path Pointer to the destination string where the characters will be copied.
 * @param str Input string containing the characters to copy.
 * 
 * @note This function assumes that the destination string is large enough to hold the copied characters.
 */
void	copy_var(char *var_path, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < (int)ft_strlen(str))
	{
		if (str[j] == '\'' || str[j] == '\"')
			j++;
		else
		{
			var_path[i] = str[j];
			i++;
			j++;
		}
	}
}

/**
 * @brief Get the new variable value from the input string.
 * 
 * This function extracts the new variable value from the input string.
 * 
 * @param var Pointer to the destination string where the value will be stored.
 * @param str Input string containing the variable and its value.
 * 
 * @note This function allocates memory for the new value string.
 */
void	get_new_var(char **var, char *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			size++;
		i++;
	}
	*var = ft_calloc(sizeof(char *), (i - size) + 1);
	if (!var)
		return ;
	copy_var(*var, str);
}

/**
 * @brief Copy the environment variable to a new array.
 * 
 * This function copies the environment variable to a new array.
 * 
 * @param tools Pointer to the tools structure containing environment variables.
 * @param new_array Pointer to the new array where the variable will be copied.
 * @param var_value Value of the variable to copy.
 * @param i Index to start copying.
 * 
 * @return Returns 1 if successful, otherwise returns 0.
 * 
 * @note This function assumes that the new array is large enough to hold the copied variable.
 *       It also frees the memory allocated for the old value.
 */
int	copy_var_to_env(t_tools *tools, char **new_array, char *var_value, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_array[j] = ft_strdup(tools->env[j]);
		if (new_array[j] == NULL)
		{
			free_list(new_array);
			free(var_value);
			return (0);
		}
		j++;
	}
	new_array[j] = ft_strdup(var_value);
	if (new_array[j] == NULL)
	{
		free(var_value);
		free_list(new_array);
		return (0);
	}
	return (1);
}
