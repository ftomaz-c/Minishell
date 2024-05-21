/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:42:47 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
/**
 * @brief Gets special character representation based on the input string.
 * 
 * This function retrieves the special character ('\t', '\n', or '\r') 
 * based on the input string.
 * 
 * @param str The input string.
 * @param i Index to start checking for the special character.
 * 
 * @return The special character if found, otherwise 0.
 * 
 * @note The input string (str) is assumed to be valid and null-terminated.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * ```
 * char special_char = get_special_char("example\tstring", 7);
 * // special_char now contains '\t'
 * ```
 */
char	get_special_char(char *str, int i)
{
	if (str[i + 3] == 't')
		return ('\t');
	else if (str[i + 3] == 'n')
		return ('\n');
	else if (str[i + 3] == 'r')
		return ('\r');
	return (0);
}

/**
 * @brief Gets a new string with special characters replaced.
 * 
 * This function creates a new string with special characters
 *  replaced based on the input string.
 * 
 * @param str The input string.
 * 
 * @return The new string with replaced special characters.
 * 
 * @note Memory is allocated within the function and needs to be freed 
 * by the caller to avoid memory leaks.
 * 
 * @warning None.
 * 
 * @see get_special_char
 * 
 * @example
 * ```
 * char *new_str = get_new_special_str("Example $'special' string");
 * // new_str now contains "Example special string"
 * free(new_str);
 * ```
 */
char	*get_new_special_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i] != '$' && str[i])
		new_str[j++] = str[i++];
	if (str[i] == '$')
	{
		new_str[j] = get_special_char(str, i);
		if (!new_str[j])
		{
			free(str);
			return (NULL);
		}
		i += 5;
		j++;
	}
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	return (new_str);
}

/**
 * @brief Checks and replaces special characters in a list of strings.
 * 
 * This function iterates through a list of strings and replaces 
 * special characters ('$' followed by '\'') with their representations.
 * 
 * @param list The list of strings.
 * 
 * @return None.
 * 
 * @note None.
 * 
 * @warning Memory for the modified strings is allocated within 
 * the function and needs to be freed by the caller to avoid memory leaks.
 * 
 * @see get_new_special_str
 * 
 * @example
 * ```
 * char *list[] = {"Example $'special' string", NULL};
 * check_special_chars(list);
 * // list[0] now contains "Example special string"
 * ```
 */
void	check_special_chars(char **list)
{
	size_t	position;
	int		index;
	char	*str;
	size_t	size;

	index = 0;
	while (list[index])
	{
		size = ft_strlen(list[index]);
		if (size > 4)
		{
			position = find_char_position_new(list[index], '$');
			if (position < size && list[index][position + 1] == '\''
				&& list[index][position + 2] == '\\'
				&& list[index][position + 4] == '\'')
			{
				str = get_new_special_str(list[index]);
				if (!str)
					break ;
				free(list[index]);
				list[index] = str;
			}
		}
		index++;
	}
}

/**
 * @brief Validates syntax of a command.
 * 
 * This function validates the syntax of a command based on certain rules.
 * 
 * @param lexer The lexer structure representing the command.
 * @param tools The tools structure containing additional flags.
 * 
 * @return 1 if syntax is valid, otherwise 0.
 * 
 * @note None.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * ```
 * t_lexer lexer;
 * t_tools tools;
 * int result = valid_syntax(&lexer, &tools);
 * // Returns 1 if syntax is valid, otherwise 0.
 * ```
 */

int	valid_token_starter(t_lexer *lexer)
{
	t_lexer	*current;

	current = lexer;
	if (lexer->token == '<' || lexer->token == '>')
	{
		while (current->next && !current->next->words)
			current = current->next;
		if (current->token == '|')
		{
			syntax_err(current->token);
			return (0);
		}
	}
	else if (lexer->token == '|')
	{
		syntax_err(current->token);
		return (0);
	}
	return (1);
}

int	valid_syntax(t_lexer *lexer, t_tools *tools)
{
	t_lexer	*current;

	if (tools->token_flag)
	{
		if (!valid_token_starter(lexer))
			return (0);
		current = lexer;
		while (current && !current->token)
			current = current->next;
		if (current->token == '|' && current->next
			&& current->next->token == '|')
		{
			syntax_err(current->token);
			return (0);
		}
		if (current->token == '>' && current->next
			&& current->next->token == '<')
		{
			syntax_err(current->token);
			return (0);
		}
	}
	return (1);
}
