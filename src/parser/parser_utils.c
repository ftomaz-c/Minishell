#include "../../includes/parser.h"

/**
 * @brief Frees the memory allocated for a string list.
 * 
 * This function frees the memory allocated for a list of strings. It iterates through
 * the list and frees each string, then frees the list itself.
 * 
 * @param str A pointer to the list of strings.
 * 
 * @note This function assumes that 'str' is a valid pointer to a list of strings, terminated by NULL.
 */

void	free_strlist(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/**
 * @brief Adds a parser node to the end of a parser linked list.
 * 
 * This function adds a parser node to the end of a parser linked list. If the list is empty,
 * the new node becomes the first node. Otherwise, it traverses the list to find the last node
 * and appends the new node to it.
 * 
 * @param lst A double pointer to the parser linked list.
 * @param new A pointer to the parser node to be added.
 * 
 * @note This function assumes that 'lst' and 'new' are valid pointers.
 */

void	ft_lstadd_parser_back(t_parser**lst, t_parser *new)
{
	t_parser	*last;

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
	new->prev = last;
}

/**
 * @brief Frees the memory allocated for a parser linked list.
 * 
 * This function frees the memory allocated for a parser linked list. It iterates through
 * the list and frees each parser node, along with any associated memory.
 * 
 * @param parser A double pointer to the parser linked list.
 * 
 * @note This function assumes that 'parser' is a valid pointer to a parser linked list.
 */

void	free_parser(t_parser **parser)
{
	t_parser	*current;
	t_parser	*next;

	current = *parser;
	if (!parser && *parser == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		if (current->str != NULL)
			free_strlist(current->str);
		if (current->redirections)
			free_lexer(&current->redirections);
		free(current);
		current = next;
	}
	*parser = NULL;
}

/**
 * @brief Initializes a parser node and parser.str list with the given start and end indices.
 * 
 * This function initializes a parser node and parser.str list with the given start and end indices. It allocates
 * memory for the node and its 'str' array based on the difference between 'end' and 'start'.
 * 
 * @param start The starting index for the parser.str list.
 * @param end The ending index for the parser.str list.
 * 
 * @return Returns a pointer to the newly initialized parser node on success, or NULL on failure.
 * 
 * @note This function assumes that 'start' and 'end' are valid indices.
 * 
 * @warning Memory allocated for the parser node and its 'str' array should be freed if the function fails.
 */

t_parser	*init_parser(int start, int end)
{
	t_parser	*node;

	node = ft_calloc(1, sizeof (t_parser));
	if (!node)
		return (NULL);
	node->str = ft_calloc(end - start + 1, sizeof(char *));
	if (!node->str)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

/**
 * @brief Finds the lexer node corresponding to the given index.
 * 
 * This function finds the lexer node corresponding to the given index in the lexer linked list.
 * It traverses the lexer list until it finds the node with the specified index.
 * 
 * @param lexer A pointer to the lexer linked list.
 * @param start The index of the lexer node to find.
 * 
 * @return Returns a pointer to the lexer node with the specified index.
 * 
 * @note This function assumes that 'lexer' is a valid pointer to a lexer linked list and that 'start' is a valid index.
 */

t_lexer	*start_token(t_lexer *lexer, int start)
{
	t_lexer		*current;

	current = lexer;
	while (current->index != start)
		current = current->next;
	return (current);
}