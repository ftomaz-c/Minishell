/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 17:23:41 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/**
 * @brief Determines the index of the history section in a line.
 * 
 * This function determines the index of the history section in a line.
 * It iterates through the characters in the line, checking if they are digits
 * until it encounters a non-digit character or the end of the line.
 * If the line starts with digits followed by a dot, it returns the index of the
 * character after the dot plus two, indicating the start of the history section.
 * 
 * @param line The line to analyze for the history section.
 * 
 * @return int The index of the history section in the line, or 0 if no history
 *             section is found.
 */
int	history_section(char *line)
{
	int	i;

	i = 0;
	if (line == NULL || *line == '\0')
		return (0);
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
	{
		if (line[i] == '\0')
			return (0);
		i++;
	}
	if (line[i] == ' ')
		return (i + 2);
	return (0);
}

/**
 * @brief Treats a string and splits it into an array of lines.
 * 
 * This function takes a string and splits it into an array of substrings, 
 * where each substring represents a line in the original string.
 * 
 * @param line_array Pointer to the array of 
 * strings where lines will be stored.
 * @param line Pointer to the string to be treated and split into lines.
 * 
 * @return None.
 */
void	treat_line(char ***line_array, char *line)
{
	int		i;
	int		j;
	int		newline;
	char	size;

	i = 0;
	j = 0;
	newline = 0;
	size = count_chr(line, '\n') + 1;
	*line_array = ft_calloc(sizeof(char **), size + 1);
	if (!(*line_array))
		return ;
	while (newline < (int)ft_strlen(line) && j < size)
	{
		newline = find_next_char_position(line, newline, '\n') + 1;
		(*line_array)[j] = ft_substr(line, i, newline - i);
		i = newline;
		j++;
	}
}

/**
 * @brief Adds a line to a line array, writes it 
 * to a history file, and frees the array.
 * 
 * This function adds a line to a dynamically allocated
 *  array of strings, then writes the modified array
 * to a history file specified by `file_path`. It also 
 * frees the memory allocated for the line array.
 * 
 * @param line The line to add to the array.
 * @param line_array Pointer to the pointer to the array of strings.
 * @param fd The file descriptor for the history file.
 * @param file_path Path to the history file.
 * 
 * @return void
 */
void	add_line(char *line, char ***line_array, int fd, char *file_path)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return ;
	add_history(line);
	treat_line(line_array, line);
	write_in_history_file(*line_array, fd, file_path);
	free_list(*line_array);
}

/**
 * @brief Checks the count of lines read from a history file.
 * 
 * This function checks if the `line_count` obtained from 
 * reading the history file is valid. If `line_count` is -1,
 * it prints an error message indicating failure to open the history file.
 * 
 * @param line_count The number of lines read from the history file.
 * @param fd The file descriptor for the history file.
 * 
 * @return Returns 1 if `line_count` is not -1, indicating
 *  success, otherwise returns 0.
 */
int	check_line_count(int line_count, int fd)
{
	if (line_count == -1)
	{
		perror("Error opening history file");
		return (0);
	}
	if (line_count != 0)
		ft_putchar_fd('\n', fd);
	return (1);
}
