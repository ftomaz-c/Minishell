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
			if (position < (int)ft_strlen(split[index]) && !find_single_quote(split[index])
			&& split[index][position + 1])
			{
				if (split[index][position + 1] == '?')
					end = position + 2;
				else
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

char *merge_split_expander(char **split)
{
	char	*str;
	char	*tmp;
	int		index;

	index = 0;
	str = ft_strdup("");
	while (split[index])
	{
		tmp = ft_strjoin(str, split[index]);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		free(str);
		str = tmp;
		index++;
	}
	return (str);
}

void	expander(char **env, char **list)
{
	int		index;
	char	**split;
	char	*tmp;

	index = 0;
	while (list[index])
	{
		split = split_expander(list[index]);
		if (split)
		{
			expand_split(env, split);
			free(list[index]);
			tmp = merge_split_expander(split);
			list[index] = tmp;
			free_list(split);
		}
		index++;
	}
}
