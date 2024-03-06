#include "../../includes/lexer.h"

/**
 * @brief Adds a word segment to a lexer node.
 * 
 * This function creates a new lexer node, allocates
 * memory for a word segment,
 * copies the word from 'word' starting from index 'start' to 'end'
 * (exclusive) into the segment,
 * and adds the segment to the end of the lexer list pointed by 'lexer'.
 * 
 * @param word The string containing the word.
 * @param start The start index of the word segment within 'word'.
 * @param end The end index of the word segment within 'word' (exclusive).
 * @param lexer Pointer to the pointer to the head of the lexer list.
 * 
 * @note This function assumes that 'word' is a null-terminated string.
 *       It also assumes that the 'lexer' pointer is pointing
 * to a valid lexer list.
 * 
 * @warning The function does not perform input validation on 'word' or 'lexer'.
 *          It may result in unexpected behavior if 'word' is not
 * a valid string or if 'lexer' is NULL.
 *          It also does not handle memory allocation failures.
 * 
 * @example
 * ```
 * char *word = "Hello";
 * t_lexer *lexer = NULL; // Assume lexer is initialized elsewhere
 * add_word_to_node(word, 0, 5, &lexer);
 * // A new lexer node containing "Hello" will be added to the end
 * of the lexer list
 * ```
 */

void	add_word_to_node(char *word, t_lexer **lexer)
{
	t_lexer	*node;
	t_lexer	*last;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	node->words = ft_strdup(word);
	if (!node->words)
	{
		free(node);
		return ;
	}
	node->token = '\0';
	if (*lexer)
	{	
		last = *lexer;
		while (last->next)
			last = last->next;
		node->index = last->index + 1;
	}
	else
		node->index = 0;
	node->next = NULL;
	node->pre = NULL;
	ft_lstaddback(lexer, node);
}
/**
 * @brief Adds a token to a lexer node.
 * 
 * This function creates a new lexer node, initializes
 * it with the provided token,
 * and adds the node to the end of the lexer list pointed by 'lexer'.
 * 
 * @param token The token to add to the lexer node.
 * @param lexer Pointer to the pointer to the head of the lexer list.
 * 
 * @note This function assumes that the 'lexer' pointer is
 * pointing to a valid lexer list.
 * 
 * @warning The function does not perform input validation on 'lexer'.
 *          It may result in unexpected behavior if 'lexer' is NULL.
 *          It also does not handle memory allocation failures.
 * 
 * @example
 * ```
 * char token = '<';
 * t_lexer *lexer = NULL; // Assume lexer is initialized elsewhere
 * add_token_to_node(token, &lexer);
 * // A new lexer node containing '<' as the token will be
 * added to the end of the lexer list
 * ```
 */

void	add_token_to_node(char token, t_lexer **lexer, t_tools *tools)
{
	t_lexer	*node;
	t_lexer	*last;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return ;
	node->words = NULL;
	node->token = token;
	if (*lexer)
	{	
		last = *lexer;
		while (last->next)
			last = last->next;
		node->index = last->index + 1;
	}
	else
		node->index = 0;
	node->next = NULL;
	node->pre = NULL;
	tools->tflag = 1;
	ft_lstaddback(lexer, node);
}
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
	while (str[i])
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
 * @brief Adds a line split into a lexer structure.
 * 
 * This function iterates through the array of strings 'line_split',
 * splits each string into words and tokens, and adds them
 * to the lexer structure.
 * 
 * @param line_split An array of strings representing the split line.
 * @param lexer Pointer to the pointer to the head of the lexer list.
 * 
 * @note This function assumes that 'line_split' is a
 * null-terminated array of strings.
 *       It also assumes that the 'lexer' pointer is pointing
 * to a valid lexer list.
 * 
 * @warning The function does not perform input validation
 * on 'line_split' or 'lexer'.
 *          It may result in unexpected behavior if 'line_split' is not
 * a valid array of strings or if 'lexer' is NULL.
 * 
 * @see add_word_to_node(), add_token_to_node(), check_if_token()
 * 
 * @example
 * ```
 * char *line_split[] = {"echo", "Hello", "world", "<", NULL};
 * t_lexer *lexer = NULL; // Assume lexer is initialized elsewhere
 * add_line_to_lexer_struct(line_split, &lexer);
 * // The lexer list will contain nodes for words ("echo", "Hello", "world")
 * and a token ('<')
 * ```
 */

void	add_line_to_lexer_struct(char **line_split, t_lexer **lexer, t_tools *tools)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	while (line_split[i] != NULL)
	{
		j = 0;
		start = 0;
		while (line_split[i][j] != '\0')
		{
			if (check_if_token_valid(line_split[i], line_split[i][j], j))
			{
				if (start < j)
					remove_quotes_add_word(line_split[i], start, j, lexer);
				add_token_to_node(line_split[i][j], lexer, tools);
				start = ++j;
			}
			else
				j++;
		}
		if (start < j)
			remove_quotes_add_word(line_split[i], start, j, lexer);
		i++;
	}
}

/**
 * @brief Lexically analyzes a line and adds it to the lexer structure.
 * 
 * This function performs lexical analysis on the input
 * 'line' by splitting it into words and tokens,
 * expanding environment variables, and adding the resulting segments
 * to the lexer structure.
 * 
 * @param line The input line to lexically analyze.
 * @param lexer Pointer to the pointer to the head of the lexer list.
 * @param envp The environment variables array for expansion.
 * 
 * @return Returns 1 on success.
 * 
 * @note This function assumes that 'line' is a null-terminated string.
 *       It also assumes that the 'lexer' pointer is
 * pointing to a valid lexer list.
 * 
 * @warning The function does not perform input validation on 'line' or 'lexer'.
 *          It may result in unexpected behavior if 'line' is not a
 * valid string or if 'lexer' is NULL.
 *          It also does not handle memory allocation failures.
 * 
 * @see init_lexer(), lexer_split(), expander(),
 * add_line_to_lexer_struct(), free_list()
 * 
 * @example
 * ```
 * char *line = "echo $HOME";
 * t_lexer *lexer = NULL; // Assume lexer is initialized elsewhere
 * char *envp[] = {"HOME=/home/user", NULL}; // Assume environment variables
 * are set elsewhere
 * lex_line(line, &lexer, envp);
 * // The lexer list will contain nodes for words ("echo", "/home/user")
 * ```
 */

int	lex_line(char *line, t_tools *tools)
{
	char	**line_split_quotes;
	char	*new_line;

	tools->lexer = NULL;
	tools->pipes = 0;
	tools->tflag = 0;
	line_split_quotes = ft_split(line, " ");
	if (!line_split_quotes)
		return (0);
	check_special_chars(line_split_quotes);
	new_line = expander(tools->env, line_split_quotes, tools);
	free_list(line_split_quotes);
	if (!new_line)
		return (0);
	line_split_quotes = lexer_split(new_line, ' ');
	free(new_line);
	if (!line_split_quotes)
		return (0);
	add_line_to_lexer_struct(line_split_quotes, &tools->lexer, tools);
	free_list(line_split_quotes);
	if (!valid_syntax(tools->lexer, tools))
		return (0);
	return (1);
}
