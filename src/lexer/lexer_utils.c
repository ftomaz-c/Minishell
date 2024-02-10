#include "../../includes/minishell.h"

int	check_unclosed_quotes(char *line) // checks if the quotes are paired, based on the first quote type found
{
	int	i;
	int	first;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	first = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			if (single_quotes == 0)
				first = 1;
			double_quotes += 1;
		}
		else if (line[i] == 39)
		{
			if (double_quotes == 0)
				first = 2;
			single_quotes += 1;	
		}
		i++;
	}
	if (first == 1)
	{
		if (double_quotes && double_quotes % 2 != 0)
			return (0);	
	}
	if (first == 2)
	{
		if (single_quotes && single_quotes % 2 != 0)
			return (0);
	}
	return (1);
}

/**
 * @brief Checks if a character is a token.
 * 
 * This function checks if the character 'c' is a token ('>', '<', '|', or '&').
 * 
 * @param c The character to check.
 * 
 * @return Returns 1 if 'c' is a token, otherwise returns 0.
 * 
 * @example
 * ```
 * char c = '>';
 * int is_token = check_if_token(c);
 * // is_token will be 1 since '>' is a token
 * ```
 */

int	check_if_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&' || c == '\n')
		return (1);
	return (0);
}

/**
 * @brief Adds a new node to the end of a lexer list.
 * 
 * This function adds the lexer node 'new' to the end of the
 * lexer list pointed by 'lst'.
 * 
 * @param lst Pointer to the pointer to the head of the lexer list.
 * @param new Pointer to the new lexer node to be added.
 * 
 * @note This function assumes that 'lst' is a valid pointer to a
 * pointer to a lexer list,
 *       and 'new' is a valid pointer to a lexer node.
 * 
 * @warning The function does not perform input validation on 'lst' or 'new'.
 *          It may result in unexpected behavior if 'lst' or 'new' is NULL.
 * 
 * @example
 * ```
 * t_lexer *lst = NULL;
 * t_lexer *new_node = malloc(sizeof(t_lexer));
 * ft_lstaddback(&lst, new_node);
 * // 'new_node' will be added to the end of the lexer list 'lst'
 * ```
 */

void	ft_lstaddback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->pre = last;
}
/**
 * @brief Frees the memory allocated for a lexer list.
 * 
 * This function frees the memory allocated for each node in
 * the lexer list pointed by 'lexer',
 * including the memory allocated for the words in each node.
 * 
 * @param lexer Pointer to the pointer to the head of the lexer list.
 * 
 * @note This function assumes that 'lexer' is a valid pointer
 * to a pointer to a lexer list.
 * 
 * @warning The function does not perform input validation on 'lexer'.
 *          It may result in unexpected behavior if 'lexer' is NULL.
 * 
 * @example
 * ```
 * t_lexer *lexer = NULL; // Assume lexer list is initialized elsewhere
 * free_lexer(&lexer);
 * // All memory allocated for the lexer list and its nodes will be freed
 * ```
 */

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*current;
	t_lexer	*next;

	current = *lexer;
	if (*lexer == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		free(current->words);
		free(current);
		current = next;
	}
	*lexer = NULL;
}
/**
 * @brief Frees the memory allocated for a null-terminated array of strings.
 * 
 * This function frees the memory allocated for each string in the array 'list',
 * as well as the memory allocated for the array itself.
 * 
 * @param list Pointer to the array of strings to free.
 * 
 * @note This function assumes that 'list' is a null-terminated array of strings.
 * 
 * @warning The function does not perform input validation on 'list'.
 *          It may result in unexpected behavior if 'list' is NULL
 * or if any of its elements are NULL.
 * 
 * @example
 * ```
 * char *list[] = {"Hello", "world", NULL};
 * free_list(list);
 * // All memory allocated for the array 'list' and its strings will be freed
 * ```
 */

void	free_list(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
