#include "../../includes/parser.h"

/**
 * @brief Adds a redirection token to the parser node.
 * 
 * This function creates a new redirection token based on 
 * the current token
 * and adds it to the list of redirections in the parser
 * node. It also updates
 * the current token pointer to the next token if it exists.
 * 
 * @param current The current token being processed.
 * @param node The parser node to which the redirection 
 * token will be added.
 * 
 * @return The next token after the redirection token, or NULL
 * if memory allocation fails.
 * 
 * @note The function assumes that the current token is a
 * redirection token ('>' or '<').
 * If current->words is not NULL, it assumes that the current
 * token has associated words.
 * 
 * @warning The function modifies the parser node's redirections
 * list and updates the current token pointer.
 * Ensure that the input parameters are valid and that memory
 * allocation is successful.
 * 
 * @see parse_tokens
 * 
 * @example
 * ```
 * t_lexer *current_token = get_next_token();
 * int start = 0;
 * t_parser *parser_node = initialize_parser();
 * while (current_token != NULL) {
 *     current_token = parse_tokens(parser_node, 
 * current_token, &start);
 *     // Handle error if current_token is NULL
 * }
 * ```
 */

t_lexer	*add_redirection(t_lexer *current, t_parser *node, int *start)
{
	t_lexer		*redirections_node;

	redirections_node = ft_calloc(1, sizeof(t_lexer));
	if (!redirections_node)
		return (NULL);
	redirections_node->index = current->index;
	redirections_node->token = current->token;
	if (current->words)
	{
		redirections_node->words = ft_strdup(current->words);
		if (!redirections_node->words)
		{
			free_lexer(&redirections_node);
			return (NULL);
		}
	}
	ft_lstaddback_lexer(&node->redirections, redirections_node);
	if (current->next)
		current = current->next;
	if (start)
		(*start)++;
	return (current);
}
