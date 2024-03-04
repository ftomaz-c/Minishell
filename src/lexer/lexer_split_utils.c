#include "../../includes/minishell.h"
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
 * 
 * @note This function assumes that 'str' is a 
 * null-terminated string.
 *       It searches for the paired quote character 'ch' starting
 * from the index 'i'.
 * 
 * @warning The function does not perform input 
 * validation on 'str'.
 *          It may result in unexpected behavior if 
 * 'str' is not a valid string.
 * 
 * @example
 * ```
 * char *str = "This is 'a sample' string";
 * int index = paired_quote(str, 8, '\'');
 * // index will be the position of the paired
 *  quote character ('a')
 * ```
 */

int	paired_quote(char *str, int i, char ch)
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
		else if (str[i] == ' ' && pair == 1)
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
 * 
 * @note This function assumes that 's' is a null-terminated string.
 * 
 * @warning The function assumes that 'i' and 'start' are valid pointers.
 *          It may result in unexpected behavior if 's' is not a valid 
 * string or if 'i' or 'start' points to invalid memory.
 * 
 * @see paired_quote()
 * 
 * @example
 * ```
 * char *s = "   'This is' a   string";
 * int i = 0;
 * int start = 0;
 * handle_white_spaces_and_quotes(s, &i, &start);
 * // After the call:
 * // i will point to the position of the paired quote
 * character ('i' in 'This is')
 * // start will point to the position of the start of the
 * substring ('T' in 'This')
 * ```
 */

void	handle_white_spaces_and_quotes(char *s, int *i, int *start)
{
	if (s[*i] == ' ')
	{
		while (s[*i] == ' ')
			(*i)++;
		*start = *i;
	}
	if (s[*i] == '\"' || s[*i] == '\'')
		*i = paired_quote(s, *i + 1, s[*i]);
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
 * 
 * @note This function assumes that 'i', 'start', and
 * 'nstart' are valid pointers.
 * 
 * @warning The function does not perform input validation on
 * 'i', 'start', or 'nstart'.
 *          It may result in unexpected behavior if
 * they point to invalid memory.
 * 
 * @example
 * ```
 * int i = 5;
 * int start = 0;
 * int nstart = 7;
 * update_start_indexes(&i, &start, &nstart);
 * // After the call:
 * // i will be decremented by 1
 * // start will be updated to 7 (value of nstart)
 * ```
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
 * 
 * @note This function assumes that 's' is a null-terminated string.
 * 
 * @warning The function does not perform input validation on 's'.
 *          It may result in unexpected behavior if 's' is not a valid string.
 * 
 * @see paired_quote()
 * 
 * @example
 * ```
 * char *s = "This is 'a sample' string";
 * int count = count_words_and_quotes(s, ' ');
 * // count will be 4 (This, is, 'a sample', string)
 * ```
 */

int	count_words_and_quotes(char *s, char c)
{
	size_t	i;
	int		word;

	i = 0;
	word = 0;
	while (i < ft_strlen(s) + 1)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			word++;
			i = paired_quote(s, i + 1, s[i]) + 1;
		}
		else
		{
			word++;
			i++;
			if ((s[i] == '\"' || s[i] == '\'') && s[i])
				i = paired_quote(s, i + 1, s[i]) + 1;
			while (s[i] && s[i] != c)
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
 * 
 * @note This function assumes that 's' is a null-terminated string.
 * 
 * @warning The function does not perform input validation on
 * 's', 'start', or 'end'.
 *          It may result in unexpected behavior if 's' is not a valid
 * string or if 'start' and 'end' are out of bounds.
 *          It also does not handle memory allocation failures.
 * 
 * @example
 * ```
 * char *s = "Hello, world!";
 * char *word = word_alloc(s, 0, 5);
 * // word will contain "Hello" (allocated dynamically)
 * ```
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
