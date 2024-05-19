/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:11:43 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

/**
 * @brief Adjusts history size and starting point based on arguments.
 * 
 * This function adjusts the history size and starting point based
 * on the provided arguments.
 * If the argument is -1, it sets the starting point and size to ensure that
 * the total number 
 * of lines in history does not exceed 1000.
 * If the argument is less than the total number of lines in history,
 * it sets the starting point and size accordingly.
 * If the argument is greater than or equal to the total number of lines 
 * in history, it sets the starting point to 0 and the 
 * size to the total number of lines in history.
 * 
 * @param arg Pointer to the argument provided.
 * @param nlines Pointer to the total number of lines in history.
 * @param size Pointer to the size to be adjusted.
 */
void	handle_history_sizes(int *arg, int *nlines, int *size)
{
	if (*arg == -1)
	{
		if (*nlines > 1000)
		{
			*arg = *nlines - 1000;
			*size = *nlines - *arg;
		}
		else
		{
			*arg = 0;
			*size = *nlines;
		}
	}
	else if (*arg < *nlines)
	{
		*size = *arg;
		*arg = *nlines - *arg;
	}
	else
	{
		*arg = 0;
		*size = *nlines;
	}
}

/**
 * @brief Copies lines from file descriptor to buffer.
 * 
 * This function reads lines from a file descriptor 
 * and copies them into a buffer
 * until either the specified number of lines are read
 *  or the end of file is reached.
 * 
 * @param buffer Pointer to the buffer where lines will be stored.
 * @param fd File descriptor for reading lines.
 * @param nlines Number of lines to copy into the buffer.
 * 
 * @return None.
 */
void	copy_buffer(char **buffer, int fd, int nlines, int arg)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (i != arg && i < nlines)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		buffer[j] = ft_strdup(line);
		j++;
		free(line);
	}
}

/**
 * @brief Prints lines from buffer.
 * 
 * This function prints lines from a buffer until 
 * it encounters a NULL pointer,
 * indicating the end of the buffer.
 * 
 * @param str Pointer to the buffer containing lines to print.
 * 
 * @return None.
 */
void	print_buffer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (!str[i])
			printf("\n");
	}
}
