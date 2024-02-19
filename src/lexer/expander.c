#include "../../includes/minishell.h"

/**
 * @brief Expands variables in a list based on environment variables.
 * 
 * This function takes a list of strings and an array of environment variables
 * and expands any variables present in the list that are prefixed with '$' 
 * by replacing them with their corresponding values from the environment.
 * 
 * @param list A pointer to an array of strings representing the list to be expanded.
 * @param env A pointer to an array of strings representing the environment variables.
 * 
 * @note The list parameter is modified in place. Any variables prefixed with '$' 
 *       in the list will be replaced with their corresponding values from the 
 *       environment variables array.
 * 
 * @warning The function assumes that the list and environment variables arrays 
 *          are properly allocated and terminated with a NULL pointer.
 * 
 * @see get_var_from_env
 * 
 * @example
 * 
 * ```
 * char *list[] = {"$HOME", "&PATH", NULL};
 * char *env[] = {"HOME=/home/user", "PATH=/usr/bin", NULL};
 * 
 * expander(list, env);
 * 
 * // After calling the function, list will be modified as follows:
 * // list[0] will contain "/home/user"
 * // list[1] will contain "/usr/bin"
 * ```
 */

/*void	expander(char **env, char **list)
{
	int		index;
	char	*var;
	char	*value;

	index = 0;
	while (list[index])
	{
		if (list[index][0] == '$')
		{
			var = ft_substr(list[index], 1, strlen(list[index]) - 1);
			value = get_var_from_env(env, var);
			free(var);
			free(list[index]);
			if (value == NULL)
				list[index] = ft_strdup("");
			else
				list[index] = ft_strdup(value);
			free(value);
		}
		index++;
	}
}*/

int	ft_isalphanum_plus_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 0 && c <= 9) || c == '_')
		return (1);
	return (0);
}

int	find_char_position_new(char *str, char c)
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

void	expander(char **env, char **list)
{
	int		index;
	char	*var;
	char	*value;
	int		position;
	int		end;

	index = 0;
	while (list[index])
	{
		if (find_char_position_new(list[index], '$') < (int)ft_strlen(list[index]))
		{
			position = find_char_position_new(list[index], '$');
			end = position + 1;
			//printf("position: %d\n", position);
 			while(list[index] && list[index][end] && ft_isalphanum_plus_underscore(list[index][end]))
 				end++;
 			//printf("end: %d\n", end);
 			var = ft_substr(list[index], position + 1, end);
 			value = get_var_from_env(env, var);
 			free(var);
 			free(list[index]);
			if (value == NULL)
				list[index] = ft_strdup("");
			else
 				list[index] = ft_strdup(value);
 			free(value);
 		}
		index++;
	}
}
