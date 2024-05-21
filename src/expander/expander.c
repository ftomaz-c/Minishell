/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:18:45 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/**
 * @brief Checks the conditions for expanding a variable in a string.
 * 
 * This function checks if the conditions are met for
 * expanding a variable in a string.
 * The conditions include ensuring the position is within the 
 * string bounds, no single quotes
 * precede the position, and the character following the position
 * is either '?' or an alphanumeric
 * character or underscore.
 * 
 * @param str The input string to be checked.
 * @param position The position in the string to be
 * checked for variable expansion.
 * @return int 1 if conditions are met for expansion, 0 otherwise.
 */
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
	if (!ft_isalnum(str[position + 1]) && str[position + 1] != '_')
		return (0);
	return (1);
}

/**
 * @brief Expands variables in an array of strings
 * based on environment variables.
 * 
 * This function iterates over an array of strings and
 * expands variables in each string
 * based on the provided environment variables. It identifies
 * variables by '$' prefix
 * and expands them using the `add_prefix_and_suffix` function.
 * 
 * @param env The array of environment variables.
 * @param split The array of strings to be expanded.
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

/**
 * @brief Merges a list of strings into a single
 * string with a specified separator.
 * 
 * This function merges a list of strings into a single
 * string, concatenating them with
 * the specified separator between each pair of strings.
 * 
 * @param list The list of strings to be merged.
 * @param separator The separator to be used between strings.
 * @return char* The merged string, or NULL on error.
 */
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

/**
 * @brief Expands a tilde (~) character in a string
 * to the home directory.
 * 
 * This function expands a tilde character in a string
 * to the home directory path.
 * If the tilde is followed by a slash or the end of the
 * string, it replaces the tilde
 * with the home directory path.
 * 
 * @param str The input string containing the tilde character.
 * @param home_var The home directory path.
 * @return char* The expanded string, or the original
 * string if the tilde is not followed
 * by a slash or the end of the string.
 */
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
