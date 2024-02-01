#include "../includes/minishell.h"

int	ft_pairedquote(char *str, int i, char ch)
{
	int pair;

	pair = 0;
	while(str[i] != '\0')
	{
		if (str[i] == ch)
			pair = 1;
		if (str[i] == ' ' && pair == 1)
			break ;
		i++;
	}
	return (i);
}

int	count_words_quotes(char *s, char c)
{
	size_t	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == 34 || s[i] == 39) && s[i])
		{
			word++;
			if (s[i] == '\"' || s[i] == '\'')
				i = ft_pairedquote(s, i + 1, s[i]) + 1;
		}
		else if (s[i] && s[i] == c)
			while (s[i] == c)
				i++;
		else
		{
			word++;
			while (s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
				i++;
		}
	}
	return (word);
}

char	*word_alloc(char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)ft_calloc((end - start) + 1, 1);
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
		if (s[i] == '\"' || s[i] == '\'')
			i = ft_pairedquote(s, i + 1, s[i]);
		else if (s[i] && s[i] == c)
			while (s[i] == c)
			{
				i++;
				start = i;
			}
		while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'')
			i++;
		if (s[i] == '\"' || s[i] == '\'') // for the scenario where a word was glued to the first quote found
			nstart = i;
		split[j] = word_alloc(s, start, i);
		i++;
		if (nstart)
		{
			start = nstart;
			i--;
			nstart = 0;
		}
		else
			start = i;
		j++;
	}
	return (split);
}

char	**ft_split_quotes(char *s, char c)
{
	char	**split;
	int		nwords;

	nwords = count_words_quotes(s, c);
	split = (char **)ft_calloc((nwords + 1), (sizeof(char *)));
	if (split)
	{
		split = create_split(s, split, nwords, c);
		return (split);
	}
	return (0);
}
