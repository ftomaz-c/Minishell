/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 20:45:36 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
/**
 * @brief Finds the position of the paired quote 
 * character within a string.
 * 
 * This function searches for the paired quote character 'ch'
 * starting from the index 'i' within the string 'str'.
 * It returns the index of the paired quote
 * character or the position
 * of the next space character after 'i' if found.
 * 
 * @param str The string to search within.
 * @param i The starting index for the search.
 * @param ch The quote character to find the pair for.
 * 
 * @return The index of the paired quote character
 *  or the position of the
 * next space character after 'i'.
 */
int	paired_quote(char *str, int i, char ch, int flag)
{
	int		pair;
	char	quote;

	pair = 0;
	quote = '\"';
	if (quote == ch)
		quote = '\'';
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			pair = 1;
		else if (pair && str[i] == quote)
		{
			ch = quote;
			pair = 0;
		}
		else if (ft_isspace_special(str[i], flag) && pair == 1)
			break ;
		i++;
	}
	return (i);
}

/**
 * @brief Handles white spaces and quotes within a string.
 * 
 * This function adjusts the index 'i' and the start index 'start'
 * based on white spaces and quotes within the string 's'.
 * If 's[i]' is a space character, it moves 'i' to the next non-space
 * character and updates 'start' accordingly.
 * If 's[i]' is a quote character ('\"' or '\''), it calls 'paired_quote()'
 * to find the position of the paired quote.
 * 
 * @param s The string to handle.
 * @param i Pointer to the current index within the string 's'.
 *        It is updated to reflect the new index after
 * handling white spaces and quotes.
 * @param start Pointer to the start index within the string 's'.
 *        It is updated to reflect the new start index
 * after handling white spaces.
 */
void	handle_white_spaces_and_quotes(char *s, int *i, int *start, int flag)
{
	if (ft_isspace_special(s[*i], flag))
	{
		while (ft_isspace_special(s[*i], flag))
			(*i)++;
		*start = *i;
	}
	if (s[*i] == '\"' || s[*i] == '\'')
		*i = paired_quote(s, *i + 1, s[*i], flag);
}

/**
 * @brief Updates the start indexes for handling substrings.
 * 
 * This function updates the start index 'start'
 * based on the value of 'nstart'.
 * If 'nstart' is non-zero, it sets 'start' to 'nstart' and decrements 'i'.
 * Otherwise, it sets 'start' to the current index 'i'.
 * 
 * @param i Pointer to the current index within the string.
 *        It may be decremented if 'nstart' is non-zero.
 * @param start Pointer to the start index within the string.
 *        It is updated based on the value of 'nstart'.
 * @param nstart Pointer to the start index for substrings within quotes.
 *        If non-zero, it indicates that the substring starts within quotes.
 */
void	update_start_indexes(int *i, int *start, int *nstart)
{
	if (*nstart)
	{
		*start = *nstart;
		(*i)--;
	}
	else
		*start = *i;
}

/**
 * @brief Counts the number of words and quotes in a string.
 * 
 * This function counts the number of words and quotes in the string 's'.
 * It considers words separated by the delimiter 'c' and
 * counts substrings within quotes as single words.
 * 
 * @param s The string to count words and quotes in.
 * @param c The delimiter character.
 * 
 * @return The number of words and quotes in the string.
 */
int	count_words_and_quotes(char *s, size_t size, int flag)
{
	size_t	i;
	int		word;

	i = 0;
	word = 0;
	while (i < size + 1)
	{
		while (i < size && ft_isspace_special(s[i], flag))
			i++;
		if (i < size && s[i] && (s[i] == '\"' || s[i] == '\''))
		{
			word++;
			i = paired_quote(s, i + 1, s[i], flag) + 1;
		}
		else
		{
			word++;
			i++;
			if (i < size && (s[i] == '\"' || s[i] == '\''))
				i = paired_quote(s, i + 1, s[i], flag) + 1;
			while (i < size && !ft_isspace_special(s[i], flag))
				i++;
		}
	}
	return (word);
}

/**
 * @brief Allocates memory for a word within a string and copies it.
 * 
 * This function allocates memory for a word within the string
 * 's' starting from index 'start' and ending at index 'end'.
 * It copies the word from 's' to the allocated memory
 * and returns a pointer to it.
 * 
 * @param s The string containing the word.
 * @param start The start index of the word within 's'.
 * @param end The end index of the word within 's'.
 * 
 * @return A pointer to the dynamically allocated memory containing the word.
 *         Returns NULL if memory allocation fails.
 */
char	*word_alloc(char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(sizeof(char), (end - start) + 1);
	if (word)
	{
		while (start < end)
		{
			word[i++] = s[start++];
		}
		return (word);
	}
	return (0);
}
