/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 19:00:56 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/**
 * @brief Retrieves a global status instance.
 * 
 * This function returns a pointer to a static instance of t_status,
 * ensuring that the same instance is used throughout the program.
 * 
 * @return Pointer to the static t_status instance.
 */
t_status	*global_status(void)
{
	static t_status	status;

	return (&status);
}

/**
 * @brief Sort an array of strings alphabetically.
 * 
 * This function sorts the array of strings alphabetically 
 * using a simple bubble sort algorithm.
 * 
 * @param env_copy Array of strings to be sorted.
 */
void	sort_array(char **env_copy)
{
	int		i;	
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (env_copy[i] && env_copy[i + 1])
	{
		tmp = env_copy[i];
		tmp1 = ft_substr(env_copy[i], 0, find_char_position(env_copy[i], '='));
		tmp2 = ft_substr(env_copy[i + 1], 0,
				find_char_position(env_copy[i + 1], '='));
		if (ft_strcmp(tmp1, tmp2) > 0)
		{
			env_copy[i] = env_copy[i + 1];
			env_copy[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
		free(tmp1);
		free(tmp2);
	}
}

/**
 * @brief Checks if a line contains only whitespace characters.
 * 
 * This function checks if a given string contains 
 * only whitespace characters.
 * 
 * @param line Pointer to the string to check.
 * 
 * @return Returns 1 if the line contains non-whitespace 
 * characters, otherwise 0.
 */
int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Checks if a character is a whitespace character.
 * 
 * This function checks if a given character is a whitespace 
 * character. If the flag is set, it only checks for space 
 * characters. Otherwise, it checks for all standard whitespace 
 * characters.
 * 
 * @param c Character to check.
 * @param flag If set, only checks for space characters.
 * 
 * @return Returns 1 if the character is a whitespace character 
 * according to the flag, otherwise 0.
 */
int	ft_isspace_special(int c, int flag)
{
	if (flag)
	{
		if (c == ' ')
			return (1);
	}
	else
	{
		if (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r')
			return (1);
	}
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
