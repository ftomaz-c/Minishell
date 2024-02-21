#include "../../includes/minishell.h"

void	handle_quote(char *line, int *flag, int *i, char quote)
{
	(*i)++;
	*flag = -1;
	while(line[*i] && line[*i] != quote)
		(*i)++;
	if (*i < (int)ft_strlen(line))
		*flag = 1;	
}

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

int	check_if_token_valid(char *str, char c, int position)
{
	int		i;
	int		flag;
	char	quote;
	int		qposition;
	// int		pair;

	i = 0;
	qposition = 0;
	flag = 0;
	if (!check_if_token(c))
	{	
		return (0);
	}
	// printf("here: %c\n", c);
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
				// printf("here ended\n");
				return (0);
			}
		}
		// if (i < (int)ft_strlen(str) && flag)
		if (flag)
		{	
			break ;
		}
		i++;
	}
	// if (position > qposition && position < i)
	// {	
	// 	// printf("checked token\n");
	// 	return (0);
	// }
	return (1);
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
	if (!lexer || *lexer == NULL)
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
