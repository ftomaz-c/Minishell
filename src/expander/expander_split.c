/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/26 22:35:55 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/**
 * @brief Checks if there are quotes in the middle of a string.
 * 
 * @param str The input string to be checked.
 * 
 * @returns int Returns 1 if there are quotes in the middle of the string,
 * otherwise returns 0.
 */
int	quotes_in_middle(char *str)
{
	int	i;

	i = 1;
	while (str[i] && i < (int)ft_strlen(str))
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Initializes the expander structure.
 * 
 * This function initializes the expander structure by
 * setting its size, index, and start members,
 * and allocates memory for the split array.
 * 
 * @param expander Pointer to the expander structure to be initialized.
 */
void	init_expander(t_expander *expander)
{
	expander->size = 1;
	expander->index = 0;
	expander->start = 0;
	expander->split = ft_calloc(expander->size, sizeof(char *));
}

/**
 * @brief Reallocates memory for the split array in the expander structure.
 * 
 * This function reallocates memory for the split
 * array in the expander structure,
 * accommodating additional elements as needed.
 * 
 * @param expander Pointer to the expander structure
 *  containing the split array.
 * @param str The input string being processed.
 * @param i The current index in the input string.
 * @return int Returns 1 on success, 0 on failure.
 */
int	realloc_split(t_expander *expander, char *str, int i)
{
	expander->size++;
	expander->split = ft_realloc(expander->split, expander->size * \
	sizeof(char *), (expander->size - 1) * sizeof(char *));
	if (!expander->split)
	{
		free_list(expander->split);
		return (0);
	}
	if (str[expander->start] == '$' && (str[expander->start + 1] == '\"'
			|| str[expander->start + 1] == '\''))
		expander->start++;
	expander->split[expander->index] = ft_substr(str, expander->start, \
	i - expander->start + 1);
	if (!expander->split[expander->index])
	{
		free_list(expander->split);
		return (0);
	}
	expander->start = i + 1;
	expander->index++;
	return (1);
}

/**
 * @brief Splits a string into parts for shell expansion.
 * 
 * This function splits a string into parts based on
 * shell expansion rules,
 * handling variable expansion, command substitution, and quoting.
 * 
 * @param str The input string to be split.
 * @return char** Returns an array of strings representing 
 * the split parts, or NULL on failure.
 */
char	**split_expander(char *str)
{
	t_expander	expander;
	int			i;

	if (!count_chr(str, '$'))
		return (NULL);
	init_expander(&expander);
	i = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '\'')
		{
			expander.start = i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] && (str[i + 1] == '\'' || str[i + 1] == '\0'
				|| str[i] == '\''))
		{
			if (!realloc_split(&expander, str, i))
				return (NULL);
		}
		i++;
	}
	expander.split[expander.index] = NULL;
	return (expander.split);
}
