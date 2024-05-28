/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 14:37:00 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
