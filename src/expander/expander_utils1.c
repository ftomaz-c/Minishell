/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/23 23:17:32 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Checks if a string in the list is expandable.
 * 
 * This function determines if the string at the current index in the given
 * list is expandable.
 * 
 * @param list An array of strings representing the list of strings.
 * @param index A pointer to an integer that represents the current index in 
 * the list.
 * 
 * @return Returns 1 if the current string contains a dollar sign ('$'), 
 * indicating it is expandable. Otherwise, returns 0.
 */
int	is_expandable(char **list, int *index)
{
	char	*tmp;
	char	*line;
	int		pos;

	if (ft_strchr(list[*index], '$'))
	{
		pos = find_char_position(list[*index], '$');
		if (ft_isdigit(list[*index][pos + 1]))
		{
			tmp = ft_strdup(list[*index]);
			free(list[*index]);
			line = ft_substr(tmp, pos + 2, (ft_strlen(tmp - pos + 1)));
			list[*index] = ft_strdup(line);
			free(tmp);
			free(line);
		}
		return (1);
	}
	if (ft_strcmp(list[*index], "<<") == 0)
	{
		(*index)++;
		treat_expandable_input(list, index);
	}
	return (0);
}

/**
 * @brief Finds the presence of single quotes in a string.
 * 
 * This function iterates through the given string 
 * `str` to find the presence of single quotes.
 * It returns 1 if at least one single quote is found, otherwise returns 0.
 * 
 * @param str The input string to search for single quotes.
 * 
 * @return Returns 1 if at least one single quote is found, otherwise returns 0.
 */
int	find_single_quote(char *str)
{
	int		i;
	char	first_quote;

	first_quote = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			first_quote = str[i];
		if (first_quote == '\'')
			return (1);
		else if (first_quote == '\"')
			break ;
		i++;
	}
	return (0);
}

/**
 * @brief Finds the position of a character within a string.
 * 
 * This function searches for the first occurrence of a specified 
 * character within a given string.
 * 
 * @param str The string to be searched.
 * @param c The character to search for.
 * 
 * @return Returns the position of the character within the string if 
 * found, otherwise returns the length of the string.
 */
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

/**
 * @brief Finds the end position of a variable name within a string.
 * 
 * This function determines the end position of a variable 
 * name within a given string.
 * The end position is defined as the position right after
 * the variable name ends, which can include
 * alphanumeric characters and underscores, but not the '=' character.
 * 
 * @param str The string to be analyzed.
 * @param position The starting position of the variable name within the string.
 * 
 * @return Returns the end position of the variable name.
 */
int	get_end_position(char *str, int position)
{
	int	end;

	if (str[position + 1] == '?')
		end = position + 2;
	else if ((str[position + 1] == '\'' && str[position + 2] == '\\'
			&& str[position + 4] == '\''))
		end = position + 4;
	else
	{
		end = position + 1;
		while (str && str[end] && (ft_isalnum(str[end]) || str[end] == '_')
			&& str[end] != '=')
			end++;
	}
	return (end);
}

/**
 * @brief Adds a prefix and suffix to a string based on a variable name.
 * 
 * This function constructs a new string by adding a prefix,
 * the value corresponding to the variable name from
 * the environment, and a suffix to the original string.
 * 
 * @param str The original string.
 * @param env The environment containing variable-value pairs.
 * @param position The position of the '$' character within the original string.
 * @param end The end position of the variable name within the original string.
 * 
 * @return Returns the modified string with the added prefix and suffix.
 */
char	*add_prefix_and_suffix(char *str, char **env, int position, int end)
{
	char	*prefix;
	char	*var;
	char	*value;
	char	*suffix;

	prefix = ft_substr(str, 0, position);
	var = ft_substr(str, position + 1, end - position - 1);
	if (ft_strncmp(var, "?", 1) == 0)
		value = ft_itoa(global_status()->nbr);
	else
		value = get_var_from_env(env, var);
	free(var);
	suffix = ft_substr(str, end, ft_strlen(str) - end);
	if (prefix[0] == '\"' && str[1] == '$')
	{
		free(prefix);
		prefix = ft_strdup("");
		value = add_quotes_to_value(value, 0, 1, 0);
	}
	else
		value = add_quotes_to_value(value, 1, 1, 0);
	str = build_str(value, prefix, suffix);
	return (str);
}
