/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:42:43 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

/**
 * @brief Removes quotes from a string.
 * 
 * This function removes single and double quotes from a given
 *  string and returns a new string without them.
 * 
 * @param str The input string from which quotes are to be removed.
 * @param i Starting index to begin processing the string.
 * 
 * @return A new string without quotes. If no quotes are found, returns NULL.
 * 
 * @note This function allocates memory for the new string. The 
 * caller is responsible for freeing this memory.
 * 
 * @warning This function assumes that the input string is 
 * null-terminated and does not modify the original string.
 * 
 * @see add_temp_to_word() function for adding temporary 
 * substrings to the result.
 * 
 * @example
 * ```
 * // Example usage of remove_quotes() function
 * char *input = "This 'is' a 'test' string";
 * int index = 0;
 * char *result = remove_quotes(input, index);
 * // The result should be "This is a test string" after removing the quotes.
 * // Remember to free the memory allocated for 'result' when done.
 * ```
 */

char	*remove_quotes(char	*str, int i)
{
	int		start;
	char	quote;
	char	*word;

	start = 0;
	word = NULL;
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			if (str[i] && (i - 1) >= 0)
				add_temp_to_word(str, &word, start, i);
			start = ++i;
			while (str[i] && str[i] != quote)
				i++;
			add_temp_to_word(str, &word, start, i);
			start = ++i;
		}
		else
			i++;
	}
	if (start < i)
		add_temp_to_word(str, &word, start, i);
	return (word);
}

/**
 * @brief Removes quotes from a substring and adds it to a word.
 * 
 * This function removes quotes from a substring of the input string,
 * adds the modified substring to a word, and frees the
 *  memory of the modified substring.
 * 
 * @param line_split The input string containing the substring.
 * @param start The starting index of the substring.
 * @param j The ending index of the substring.
 * @param lexer Pointer to the lexer structure.
 * 
 * @note This function assumes that the input string is null-terminated.
 */

void	remove_quotes_add_word(char *line, int start, int j, t_lexer **lexer)
{
	char	*new;
	char	*word_no_quotes;
	int		i;

	i = 0;
	new = ft_substr(line, start, j - start);
	word_no_quotes = remove_quotes(new, i);
	free(new);
	add_word_to_node(word_no_quotes, lexer);
	free(word_no_quotes);
}

/**
 * @brief Handles quotes within a string.
 * 
 * This function advances the index to the next occurrence 
 *of a specified quote character in the string,
 * updating a flag to indicate whether the quote is closed or not.
 * 
 * @param line The input string.
 * @param flag Pointer to an integer flag indicating the status 
 *of the quote (closed or not).
 * @param i Pointer to the index within the string.
 * @param quote The quote character to handle.
 * 
 * @note This function modifies the values pointed to by 'flag' and 'i'.
 * 
 * @see check_unclosed_quotes() function for checking if 
 *quotes are properly closed.
 * 
 * @warning This function assumes that the input string is null-terminated.
 */

void	handle_quote(char *line, int *flag, int *i, char quote)
{
	(*i)++;
	*flag = -1;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (*i < (int)ft_strlen(line))
		*flag = 1;
}

/**
 * @brief Checks if quotes in a string are properly closed.
 * 
 * This function checks whether single and double quotes in the 
 * given string are properly closed.
 * 
 * @param line The input string to check.
 * 
 * @return Returns 0 if there are unclosed quotes, otherwise returns 1.
 * 
 * @see handle_quote() function for handling individual quotes.
 * 
 * @warning This function assumes that the input string is null-terminated.
 */

int	check_unclosed_quotes(char *line)
{
	int		i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	while (i < (int)ft_strlen(line))
	{
		if (line[i] == 34)
		{
			quote = 34;
			handle_quote(line, &flag, &i, quote);
		}
		if (line[i] == 39)
		{
			quote = 39;
			handle_quote(line, &flag, &i, quote);
		}
		i++;
	}
	if (i > (int)ft_strlen(line) && flag == -1)
		return (0);
	return (1);
}

/**
 * @brief Adds a temporary substring to a word.
 * 
 * This function adds a temporary substring of the input string to a word.
 * 
 * @param str The input string containing the substring.
 * @param word Pointer to the word to which the substring will be added.
 * @param start The starting index of the substring.
 * @param i The ending index of the substring.
 * 
 * @note This function allocates memory for the new word. The caller 
 * is responsible for freeing this memory.
 * 
 * @warning This function assumes that the input string is null-terminated.
 */

void	add_temp_to_word(char *str, char **word, int start, int i)
{
	char	*new_word;
	char	*temp;

	new_word = NULL;
	temp = ft_substr(str, start, i - start);
	if (!(*word))
		*word = ft_strdup(temp);
	else
	{
		new_word = ft_strjoin(*word, temp);
		free(*word);
		*word = new_word;
	}
	free(temp);
}
