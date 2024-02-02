#include "../../includes/minishell.h"

/**
 * @brief Brief description of the function create_split.
 * 
 * Detailed description of the function, including its purpose, behavior, and any important details.
 * Mention any assumptions, limitations, or dependencies.
 * 
 * @param param1 s is the line to be split.
 * @param param2 split is where the splitted line will be stored.
 * @param param3 the total number of words to be splitted (obtained in count words).
 * @param param4 is the main delimiter, in this case " ".
 * 
 * @return Return value is the splitted array.
 * 
 * @note Any additional notes about the function, such as error handling, performance considerations, etc.
 *  This function splits a sentence by words, considering the space as a delimiter, however if the function encounters quotes,
 *  it will consider all the words between the quotes as one single word, and will store them as such
 * @warning Any warnings or caveats about using the function.
 * 			function create_split is too big!!
 * @see Any related functions, structures, or documentation.
 * 
 * @example Example usage of the function.
 * 
 * ```
 * // Example code demonstrating how to use the function
 * // Include any necessary setup or input/output
 * // Provide comments to explain the example
 * 
 * minishell ➜  dsj jh sdgh"dihi vj" dkhdsj jh sdgh"dihi vj" dkh oj " rci" erihf e
 *	word: dsj
 *	word: jh
 *	word: sdgh
 *	word: "dihi vj" dkh oj " rci"
 *	word: erihf
 *	word: e
 * ```
 */

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
		while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'')
			i++;
		if (s[i] == '\"' || s[i] == '\'') // for the scenario where a word was glued to the first quote found
			nstart = i;
		split[j] = word_alloc(s, start, i);
		i++;
		j++;
		update_start_indexes(&i, &start, &nstart);
	}
	return (split);
}

char	**lexer_split(char *s, char c)
{
	char	**split;
	int		nwords;

	nwords = count_words_and_quotes(s, c);
	split = (char **)ft_calloc((nwords + 1), (sizeof(char *)));
	if (split)
	{
		split = create_split(s, split, nwords, c);
		return (split);
	}
	return (0);
}