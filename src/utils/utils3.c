#include "../../includes/utils.h"

/**
 * @brief Sort an array of strings alphabetically.
 * 
 * This function sorts the array of strings alphabetically 
 * using a simple bubble sort algorithm.
 * 
 * @param env_copy Array of strings to be sorted.
 * 
 * @note This function assumes that the array is null-terminated.
 * 
 * @see strcmp()
 * 
 * @example
 */

void	sort_array(char **env_copy)
{
	int		i;	
	char	*tmp;

	i = 0;
	while (env_copy[i] && env_copy[i + 1])
	{
		tmp = env_copy[i];
		if (strcmp(env_copy[i], env_copy[i + 1]) > 0)
		{
			env_copy[i] = env_copy[i + 1];
			env_copy[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

/**
 * @brief Checks if a line contains only whitespace characters.
 * 
 * This function checks if a given string contains 
 * only whitespace characters.
 * 
 * @param line Pointer to the string to check.
 * 
 * @return Returns 1 if the line contains non-whitespace 
 * characters, otherwise 0.
 * 
 * @note This function assumes that `line` points to a valid
 *  null-terminated string.
 * 
 * @warning None.
 * 
 * @see ft_isspace().
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char *str = "   ";
 * int result = check_empty_line(str);
 * ```
 */
int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}
