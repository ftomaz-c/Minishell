/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:42:39 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
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

void	ft_lstaddback_lexer(t_lexer **lst, t_lexer *new)
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
 * @brief Checks if a token character is valid at a specified 
 * position within a string.
 * 
 * This function checks if the token character at the 
 * specified position is valid,
 * considering the presence of single or double quotes.
 * 
 * @param str The input string.
 * @param c The token character to check.
 * @param position The position of the token character.
 * 
 * @return Returns 0 if the token is not valid at the specified 
 * position, otherwise returns 1.
 * 
 * @warning This function assumes that the input string
 *  is null-terminated.
 */

int	is_fd_token(char *str, char c, int position)
{
	int	i;

	i = 1;
	if (ft_isdigit(c))
	{
		while (position - i >= 0 && ft_isdigit(str[position - i]))
			i++;
		if (position - i >= 0 && !ft_isdigit(str[position - i]))
			return (0);
		i = 0;
		while (str[position + i] && ft_isdigit(str[position + i]))
			i++;
		if (check_if_token(str[position + i]))
			return (1);
	}
	return (0);
}

int	check_if_token_valid(char *str, char c, int position)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (is_fd_token(str, c, position))
		return (1);
	if (!check_if_token(c))
		return (0);
	if (!check_token_flag(str, i, flag, position))
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
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
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
		if (current->words)
			free(current->words);
		free(current);
		current = next;
	}
	*lexer = NULL;
}
