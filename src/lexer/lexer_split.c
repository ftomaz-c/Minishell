#include "../../includes/minishell.h"

void	handle_characters(char *s, int *i, int *start)
{
	int	tmp;

	while(s[*i] && (s[*i] != ' ' && s[*i] != '\"' && s[*i] != '\''))
		(*i)++;
	if (s[*i] == '\"' || s[*i] == '\'')
	{	
		if (s[*i - 1] && s[*i - 1] != ' ')
		{
			tmp = (*i);
			while (s[*i] != ' ')
				(*i)--;
			*start = ++(*i);
			(*i) = tmp;
		}
		*i = paired_quote(s, *i + 1, s[*i]);
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

//  while str
// if quote is found, equal to first quote, until next is found, i++. then until white space
// i++
// else if no quote is foudn and char is found, start is equal to that, iterate

 char	**create_split(char *s, char **split, int nwords, char c)
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
		if (s[i] == '\"' || s[i] == '\'' || s[i] == ' ')
			handle_white_spaces_and_quotes(s, &i, &start);
		if (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'')
			handle_characters(s, &i, &start);
		split[j] = word_alloc(s, start, i);
		i++;
		j++;
		update_start_indexes(&i, &start, &nstart);
	}
	return (split);
}

// char	**create_split(char *s, char **split, int nwords, char c)
// {
// 	int	i;
// 	int	j;
// 	int	start;
// 	int	nstart;

// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	nstart = 0;
// 	while (i < (int)ft_strlen(s) && j < nwords)
// 	{
// 		if (s[i] == '\"' || s[i] == '\'' || s[i] == ' ')
// 			handle_white_spaces_and_quotes(s, &i, &start);
// 		if (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'')
// 			handle_characters(s, &i, &start);
// 		split[j] = word_alloc(s, start, i);
// 		i++;
// 		j++;
// 		update_start_indexes(&i, &start, &nstart);
// 	}
// 	return (split);
// }

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

char	**lexer_split(char *s, char c)
{
	char	**split;
	int		nwords;

	nwords = count_words_and_quotes(s, c);
	// printf("words count: %d\n", nwords);
	split = (char **)ft_calloc((nwords + 1), (sizeof(char *)));
	if (split)
	{
		split = create_split(s, split, nwords, c);
		return (split);
	}
	return (0);
}
