#include "../../includes/minishell.h"

/**
 * @brief Expands environment variables within a list of strings.
 * 
 * This function searches for environment variable references (starting with '$') within each string
 * in the list and replaces them with their corresponding values from the environment.
 * 
 * @param env The environment containing variable-value pairs.
 * @param list The list of strings to be processed.
 * 
 * @return None.
 * 
 * @note The function modifies the strings in the list in place.
 * 
 * @see find_char_position_new, get_end_position, add_prefix_and_suffix
 * 
 * @example
 * ```
 * char *environment[] = {"USER=John", "HOME=/home/john", NULL};
 * char *list[] = {"Welcome, $USER!", "Your home directory is $HOME.", NULL};
 * expander(environment, list);
 * // list will be {"Welcome, John!", "Your home directory is /home/john.", NULL}
 * ```
 */

void	expander(char **env, char **list)
{
	int		index;
	int		position;
	int		end;
	char	*str;

	index = 0;
	while (list[index])
	{
		position = find_char_position_new(list[index], '$');
		if (position < (int)ft_strlen(list[index]) && !find_single_quote(list[index]))
		{
			if (list[index][position + 1] == '?')
				end = position + 2;
			else
				end = get_end_position(list[index], position);
			str = add_prefix_and_suffix(list[index], env, position, end);
			free(list[index]);
			list[index] = ft_strdup(str);
			free(str);
		}
		index++;
	}
}
