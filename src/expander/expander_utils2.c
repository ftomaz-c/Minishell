/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/26 18:35:15 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/**
 * @brief Treats and processes expandable input strings by handling special
 * characters.
 * 
 * This function processes an array of strings, specifically focusing on the
 * string at the given index. It allocates a new string, copies the contents 
 * while handling special characters (e.g., skipping certain characters 
 * following a '$' sign), and replaces the original string with the processed
 * one.
 * 
 * The function handles cases where a '$' sign is followed by either a single 
 * quote (') or a double quote ("). In such cases, it skips the quote character.
 * 
 * @param list An array of strings to be processed.
 * @param index A pointer to the index of the string within the list to be
 * treated.
 */
void	treat_expandable_input(char **list, int *index)
{
	char	*tmp;
	int		i;
	int		j;

	if (list[*index])
	{
		tmp = ft_calloc(sizeof(char), ft_strlen(list[*index]) + 1);
		i = 0;
		j = 0;
		while (list[*index][i])
		{
			if (list[*index][i] == '$' && (list[*index][i + 1] == '\''
				|| list[*index][i + 1] == '\"'))
				i++;
			tmp[j++] = list[*index][i++];
		}
		free(list[*index]);
		list[*index] = ft_strdup(tmp);
		free(tmp);
	}
}

/**
 * @brief Adds quotes around a string.
 * 
 * This function adds quotes around a given string, with
 *  the option to choose single or double quotes.
 * If the string is already enclosed in quotes, it leaves it unchanged.
 * 
 * @param j Starting index for the value array.
 * @param str The input string.
 * @param quote The desired quote character (' or ").
 * @param value The array to store the modified string.
 * 
 * @return The modified string with added quotes.
 */
char	*add_quotes(int j, char *str, char quote, char *value)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!value[0])
		{
			if (quote == '\'')
				quote = '\"';
			else
				quote = '\'';
			value[0] = quote;
		}
		value[j] = str[i];
		i++;
		j++;
		if (str[i] == '\0')
			break ;
	}
	value[j] = quote;
	free(str);
	return (value);
}

/**
 * @brief Retrieves the type of quotation mark at the
 * specified position in a string.
 * 
 * This function examines the characters in a string starting
 * from the specified position
 * to find the type of quotation mark encountered, if any.
 * 
 * @param str The input string to be examined.
 * @param i The starting position in the string to begin the search.
 * @return char The quotation mark found (' or "), or '\0'
 * if none is found.
 */
char	get_quote_flag(char *str, int i)
{
	char	quote;

	quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			break ;
		}
		i++;
	}
	return (quote);
}

/**
 * @brief Adds quotes to a string value if it's not already quoted.
 * 
 * This function adds quotes around a string value if it's 
 * not already enclosed in quotes.
 * It checks the first occurrence of single or double quotes in 
 * the string to determine the quote character to use.
 * 
 * @param str The input string.
 * @param flagquote Flag indicating whether to trim spaces
 * from the input string.
 * @param j Starting index for the value array.
 * @param i Starting index for iterating through the input string.
 * 
 * @return The modified string with added quotes (if necessary).
 */
char	*add_quotes_to_value(char *str, int flagquote, int j, int i)
{
	char	*value;
	char	*tmp;
	char	quote;

	quote = '\0';
	if (str == NULL)
		return (NULL);
	if (flagquote == 2)
		quote = '\'';
	else
		quote = get_quote_flag(str, i);
	if (quote == '\0')
		return (str);
	value = ft_calloc(sizeof(char *), ft_strlen(str) + 2);
	if (!value)
		return (NULL);
	if (flagquote)
	{
		tmp = ft_strtrim(str, " ");
		free(str);
		str = tmp;
	}
	value = add_quotes(j, str, quote, value);
	return (value);
}

/**
 * @brief Builds a string by concatenating prefix, value, and suffix.
 * 
 * This function builds a string by concatenating 
 * a prefix, a value, and a suffix.
 * If the value is NULL, it's replaced with an empty string.
 * 
 * @param value The value to be concatenated.
 * @param prefix The prefix string.
 * @param suffix The suffix string.
 * 
 * @return The concatenated string.
 */
char	*build_str(char *value, char *prefix, char *suffix, char *var)
{
	char	*str;
	char	*tmp;

	if (value == NULL)
		tmp = ft_strjoin(prefix, "");
	else
		tmp = ft_strjoin(prefix, value);
	str = ft_strjoin(tmp, suffix);
	free(var);
	free(value);
	free(tmp);
	free(suffix);
	free(prefix);
	return (str);
}
