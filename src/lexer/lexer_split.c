/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 20:46:32 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
/**
 * @brief Displays a syntax error message.
 * 
 * This function displays a syntax error message indicating the unexpected token.
 * 
 * @param token The unexpected token.
 * 
 * @return None.
 */
void	syntax_err(char token)
{
	g_status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

/**
 * @brief Handles characters within a string, 
 * updating the index and start position.
 * 
 * This function handles characters within a string, 
 * updating the index and start position pointers accordingly.
 * It advances the index until encountering a space, 
 * double quote, or single quote character.
 * If a quote character is found, it adjusts the start
 *  position to exclude the quote character itself and its contents.
 * 
 * @param s     Pointer to the string to handle.
 * @param i     Pointer to the current index within the string.
 * @param start Pointer to the start position within the string.
 */
void	handle_characters(char *s, int *i, int *start, int flag)
{
	int	tmp;

	while (s[*i] && (!ft_isspace_special(s[*i], flag)
			&& s[*i] != '\"' && s[*i] != '\''))
		(*i)++;
	if (s[*i] == '\"' || s[*i] == '\'')
	{
		if (s[*i] && s[*i - 1] && s[*i - 1] != ' ')
		{
			tmp = (*i);
			while (*i >= 0 && s[*i] && s[*i] != ' ')
				(*i)--;
			*start = ++(*i);
			(*i) = tmp;
		}
		*i = paired_quote(s, *i + 1, s[*i], flag);
	}
}

/**
 * @brief Splits a string into an array of substrings
 * based on a delimiter character.
 * 
 * This function splits the string 's' into 'nwords' substrings,
 * using the delimiter 'c'.
 * It allocates memory for 'split' and assigns each substring to the
 * corresponding index in the array.
 * It also handles quotes within the string.
 * 
 * @param s The string to split.
 * @param split An array of strings to store the substrings.
 * @param nwords The maximum number of words to split the string into.
 * @param c The delimiter character (space).
 * 
 * @return An array of substrings split from the original string.
 *         The 'split' array contains pointers to dynamically allocated memory.
 */
char	**create_split(char *s, char **split, int nwords, int flag)
{
	int	i;
	int	j;
	int	start;
	int	nstart;

	i = 0;
	j = 0;
	start = 0;
	nstart = 0;
	while (i < (int)ft_strlen(s) && j < nwords)
	{
		if (s[i] == '\"' || s[i] == '\'' || ft_isspace_special(s[i], flag))
			handle_white_spaces_and_quotes(s, &i, &start, flag);
		if (s[i] && s[i] != ' ' && s[i] != '\"' && s[i] != '\'')
			handle_characters(s, &i, &start, flag);
		split[j] = word_alloc(s, start, i);
		i++;
		j++;
		update_start_indexes(&i, &start, &nstart);
	}
	return (split);
}

/**
 * @brief Splits a string into an array of substrings for
 * lexical analysis.
 * 
 * This function splits the string 's' into substrings for lexical
 * analysis based on the delimiter 'c'.
 * It first counts the number of words and quotes in 's' to determine the
 * size of the split array.
 * Then, it allocates memory for the split array and calls 'create_split()'
 * to populate it with substrings.
 * 
 * @param s The string to split.
 * @param c The delimiter character.
 * 
 * @return An array of substrings split from the original string
 * for lexical analysis.
 *         The 'split' array contains pointers to dynamically allocated memory.
 *         Returns NULL if memory allocation fails.
 */
char	**lexer_split(char *s, int flag)
{
	char	**split;
	int		nwords;
	int		size;

	size = ft_strlen(s);
	nwords = count_words_and_quotes(s, size, flag);
	split = ft_calloc((nwords + 1), (sizeof(char *)));
	if (split)
	{
		split = create_split(s, split, nwords, flag);
		return (split);
	}
	return (0);
}

/**
 * @brief Checks if a specified position within a string is 
 * inside a quoted section.
 * 
 * This function iterates through the string starting from index 
 * i and checks if the specified position
 * is within a quoted section delimited by single or double quotes.
 * It helps in identifying whether 
 * certain characters in the string are inside quotes or not.
 * 
 * @param str The string to be checked.
 * @param i Starting index in the string from where to check.
 * @param flag Flag indicating whether the specified position is inside a 
 * quoted section (0 if inside, 1 otherwise).
 * @param position The position to be checked if it's inside a quoted section.
 * 
 * @return Returns 0 if the specified position is inside a quoted 
 * section, 1 otherwise.
 */
int	check_token_flag(char *str, int i, int flag, int position)
{
	char	quote;
	int		qposition;

	qposition = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			qposition = i;
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote && position < i && position > qposition)
			{
				flag = 1;
				return (0);
			}
		}
		if (flag)
			break ;
		i++;
	}
	return (1);
}
