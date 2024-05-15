#include "../../includes/lexer.h"
/**
 * @brief Displays a syntax error message.
 * 
 * This function displays a syntax error message indicating the unexpected token.
 * 
 * @param token The unexpected token.
 * 
 * @return None.
 * 
 * @note None.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * ```
 * syntax_err('$');
 * // Displays "bash: syntax error near unexpected token '$'"
 * ```
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
 * 
 * @note This function assumes the validity of the input 
 * string and index pointers.
 *       It modifies the i and start pointers to reflect the
 *  updated positions.
 * 
 * @warning Behavior is undefined if s, i, or start is NULL or 
 * if the index pointers go out of bounds.
 * 
 * @see paired_quote
 * 
 * @example
 * ```
 * // Example usage of handle_characters function
 * char *s = "This is a \"quoted string\" with 'single quotes'";
 * int i = 0, start = 0;
 * handle_characters(s, &i, &start); // Handle characters in the string
 * // After function call, i and start will be updated 
 * based on encountered characters.
 * ```
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
 * 
 * @note This function assumes that the 'split' array is pre-allocated
 * with enough space to store 'nwords' strings.
 *       The function modifies the contents of 'split' to contain the substrings.
 * 
 * @warning The function assumes that 's' is a null-terminated string.
 *          It does not check for buffer overflows in 'split' or 's'.
 *          Make sure 'split' has enough space to accommodate the substrings.
 * 
 * @see word_alloc(), update_start_indexes(), handle_white_spaces_and_quotes()
 * 
 * @example
 * ```
 * char *s = "Hello, world!";
 * char *split;
 * int nwords = 2;
 * char delimiter = ' ';
 * create_split(s, split, nwords, delimiter);
 * // split[0] contains "Hello,"
 * // split[1] contains "world!"
 * // split[2] contains NULL (if there are no more words)
 * ```
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
 * 
 * @note This function assumes that 's' is a null-terminated string.
 *       It allocates memory for the 'split' array based on the number
 * of words and quotes in 's'.
 * 
 * @warning The function does not perform input validation on 's'.
 *          It may result in unexpected behavior if 's' is not a valid string
 * or if memory allocation fails.
 * 
 * @see create_split(), count_words_and_quotes()
 * 
 * @example
 * ```
 * char *s = "This is a sample string";
 * char **result = lexer_split(s, ' ');
 * // result[0] contains "This"
 * // result[1] contains "is"
 * // result[2] contains "a"
 * // result[3] contains "sample"
 * // result[4] contains "string"
 * // result[5] contains NULL (if there are no more words)
 * ```
 */

char	**lexer_split(char *s, char c, int flag)
{
	char	**split;
	int		nwords;
	int		size;

	size = ft_strlen(s);
	nwords = count_words_and_quotes(s, c, size, flag);
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
 * 
 * @note This function assumes that the input string is properly null-terminated.
 * 
 * @warning This function assumes that the input position is 
 * within the bounds of the string.
 * 
 * @see None.
 * 
 * @example
 * 
 * ```
 * // Example usage of the function
 * char *str = "This is a 'quoted' string";
 * int flag = 0;
 * int position = 12; // Index of the character 'q' in the example string
 * int result = check_token_flag(str, 0, flag, position);
 * // After the function call, result should be 0 indicating that
 * the position is inside a quoted section.
 * ```
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
