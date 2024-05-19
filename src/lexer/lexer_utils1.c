/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:13:01 by crebelo-         ###   ########.fr       */
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
 * @brief Checks if a character token represents a file descriptor in a string.
 * 
 * This function checks if a character token at a specified position in a string
 * represents a file descriptor. A character is considered a file descriptor if
 * it is a digit preceded by digits and followed by a non-digit token.
 * 
 * @param str The input string to be checked.
 * @param c The character token to be checked.
 * @param position The position of the character token in the string.
 * @return int 1 if the character token represents a file
 * descriptor, 0 otherwise.
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
 */
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
