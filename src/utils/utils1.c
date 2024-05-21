/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:44:28 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
/**
 * @brief Find the position of a character in a string.
 * 
 * This function finds the position of the specified
 *  character in the input string.
 * 
 * @param str Input string to search.
 * @param c Character to find.
 * 
 * @return Returns the position of the character in
 *  the string, or the length of the string if the character is not found.
 */
int	find_char_position(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}
/**
 * @brief Finds the next occurrence of a character in a string.
 * 
 * This function searches for the next occurrence of a specified 
 * character in the given string starting from the specified index.
 * 
 * @param str The input string to search.
 * @param i Starting index to begin searching.
 * @param c The character to search for.
 * 
 * @return The index of the next occurrence of the character 'c' 
 * in the string 'str' starting from index 'i'.
 * If 'c' is not found, returns the index 'i'.
 * 
 * @note This function assumes that the input string is null-terminated.
 * 
 * @example
 * ```
 * // Example usage of find_next_char_position() function
 * char *input = "example string";
 * int index = 0;
 * char search_char = 'm';
 * int result = find_next_char_position(input, index, search_char);
 * // The result should be 5, as 'm' is found at index 5 in "example string".
 * ```
 */

int	find_next_char_position(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief Counts the occurrences of a character in a string.
 * 
 * This function counts the occurrences of a specified 
 *  character in a given string.
 * 
 * @param line Pointer to the string in which
 *  to search for occurrences.
 * @param c The character to count occurrences of.
 * 
 * @return Returns the number of occurrences of the 
 * character in the string.
 * 
 * @note This function assumes that `line` points 
 * to a valid null-terminated string.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char *str = "hello world";
 * char c = 'o';
 * int count = count_chr(str, c);
 * ```
 */
int	count_chr(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Counts the number of lines in a file.
 * 
 * This function opens the specified file in read-only 
 * mode and counts the number of lines
 * by repeatedly reading lines until the end of the file is reached.
 * 
 * @param filename The name of the file to count lines from.
 * 
 * @return The number of lines in the file if successful,
 *  or -1 if an error occurs.
 * 
 * @note This function assumes that the file exists
 * and is accessible.
 *       It uses the get_next_line function to read
 * lines from the file.
 *       The memory for each line is allocated dynamically 
 * and freed after use.
 */

int	count_lines_in_file(const char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close (fd);
	return (count);
}
/**
 * @brief Counts the number of non-null pointers in a string array.
 * 
 * This function counts the number of non-null 
 * pointers in a string array until encountering a NULL pointer.
 * 
 * @param list Pointer to the string array to count lines in.
 * 
 * @return The number of non-null pointers in the string array.
 * 
 * @note This function assumes the validity of the input string array.
 * 
 * @warning Behavior is undefined if list is NULL 
 * or if the string array is corrupted.
 * 
 * @see None
 * 
 * @example
 * ```
 * // Example usage of count_lines function
 * char **list = {"line1", "line2", "line3", NULL};
 * int line_count = count_lines(list);
 * // Count the number of lines in the string array
 * // line_count will be 3.
 * ```
 */

int	count_lines(char **list)
{
	int	line_count;

	line_count = 0;
	while (list[line_count])
		line_count++;
	return (line_count);
}
