#include "../../includes/expander.h"

int	check_conditions_expander(char *str, int position)
{
	if (!(position < (int)ft_strlen(str)))
		return (0);
	if (find_single_quote(str))
		return (0);
	if (!(str[position + 1]))
		return (0);
	if (str[position + 1] == '?')
		return (1);
	if (!(ft_isalphanum_or_underscore(str[position + 1])))
		return (0);
	return (1);
}

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
			if (check_conditions_expander(split[index], position))
			{
				end = get_end_position(split[index], position);
				str = add_prefix_and_suffix(split[index], env, position, end);
				free(split[index]);
				split[index] = ft_strdup(str);
				free(str);
			}
			if (end == 0)
				break ;
		}
		index++;
	}
}

char	*merge_list_of_strings(char **list, char *separator)
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

char	*expand_tilde(char *str, char *home_var)
{
	char	*tmp;
	char	*new_str;

	new_str = "\0";
	if (str[0] == '~' && (str[1] == '\0' || str[1] == '/'))
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 1);
		new_str = ft_strjoin(home_var, tmp);
		free(tmp);
		free(str);
		return (new_str);
	}
	return (str);
}

/**
 * @brief Expands environment variables within a list of strings.
 * 
 * This function searches for environment variable references
 *  (starting with '$') within each string
 * in the list and replaces them with their corresponding 
 * values from the environment.
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
 * char *list[] = {"Welcome, $USER!", 
 * "Your home directory is $HOME.", NULL};
 * expander(environment, list);
 * // list will be {"Welcome, John!", "Your home 
 * directory is /home/john.", NULL}
 * ```
 */

char	*expander(char **env, char **list, t_tools *tools)
{
	int		index;
	char	**split;
	char	*line;

	(void)tools;
	index = 0;
	while (list[index])
	{
		split = split_expander(list[index]);
		if (split)
		{
			expand_split(env, split);
			free(list[index]);
			list[index] = merge_list_of_strings(split, NULL);
			free_list(split);
		}
		else
			list[index] = expand_tilde(list[index], tools->home);
		index++;
	}
	line = merge_list_of_strings(list, " ");
	return (line);
}
