/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 20:37:54 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

	i = 0;
	while (env_copy[i] && env_copy[i + 1])
	{
		tmp = env_copy[i];
		if (strcmp(env_copy[i], env_copy[i + 1]) > 0)
		{
			env_copy[i] = env_copy[i + 1];
			env_copy[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
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
