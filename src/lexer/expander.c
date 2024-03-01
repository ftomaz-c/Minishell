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

void	expand_split(char **env, char **split)
{
	char	*str;
	int		index;
	int		position;
	int		end;

	index = 0;
	while (split[index])
	{
		while (1)
		{
			end = 0;
			position = find_char_position_new(split[index], '$');
			if (position < (int)ft_strlen(split[index]) && !find_single_quote(split[index]) && split[index][position + 1])
			{
				end = get_end_position(split[index], position);
				str = add_prefix_and_suffix(split[index], env, position, end);
				free(split[index]);
				split[index] = ft_strdup(str);
				free(str);
			}
			if (end == 0)
				break;
		}
		index++;
	}
}

char *merge_list_of_strings(char **list, char *separator)
{
	char	*str;
	char	*tmp;
	int		index;

	index = 0;
	str = ft_strdup("");
	while (list[index])
	{
		tmp = ft_strjoin(str, list[index]);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		free(str);
		if (list[index + 1] && separator)
			str = ft_strjoin(tmp, separator);
		else
			str = ft_strdup(tmp);
		free(tmp);
		index++;
	}
	return (str);
}

char	*expander(char **env, char **list)
{
	int		index;
	char	**split;
	char	*tmp;
	char	*line;

	index = 0;
	while (list[index])
	{
		split = split_expander(list[index]);
		if (split)
		{
			expand_split(env, split);
			free(list[index]);
			tmp = merge_list_of_strings(split, NULL);
			list[index] = tmp;
			free_list(split);
		}
		index++;
	}
	line = merge_list_of_strings(list, " ");
	return (line);
}
