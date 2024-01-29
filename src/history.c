/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:43:46 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/29 16:05:33 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Counts the number of lines in a file.
 * 
 * This function opens the specified file in read-only mode and counts the number of lines
 * by repeatedly reading lines until the end of the file is reached.
 * 
 * @param filename The name of the file to count lines from.
 * 
 * @return The number of lines in the file if successful, or -1 if an error occurs.
 * 
 * @note This function assumes that the file exists and is accessible.
 *       It uses the get_next_line function to read lines from the file.
 *       The memory for each line is allocated dynamically and freed after use.
 */

// Function to count the number of lines in a file
int count_lines_in_file(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
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
	return(count);
}

/**
 * @brief Adds a line to a history file and updates the line count.
 * 
 * This function appends the provided line to the history file ".minishell_history",
 * along with the current line count followed by a period and space.
 * It also updates the line count by reading the current number of lines in the history file.
 * 
 * @param line The line to be added to the history file. This should be a null-terminated string
 *             obtained from the readline function or similar. The function does not modify the contents of the string.
 * 
 * @note The function assumes that ".minishell_history" exists in the current directory.
 *       If the file does not exist, it will be created.
 *       The function also assumes that the provided line is properly formatted and does not contain newline characters,
 *       as newline characters will be automatically appended to the line when written to the file.
 *       If the file or line cannot be processed, appropriate error messages will be printed to stderr.
 *       Ensure that the file has appropriate permissions for writing.
 *       The function may allocate additional memory temporarily while reading the file.
 * 
 * @warning This function does not handle concurrent access to the history file. If multiple instances of the program
 *           attempt to write to the history file simultaneously, unexpected behavior may occur.
 * 
 * @see count_lines_in_file
 */

// Function to add a line to a history file
void    add_history_file(char *line)
{
	int	fd;
	int	line_count;
	
	if (line == NULL)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (line && *line)
	{		
		fd = open(".minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Error opening history file");
			return ;
		}
		add_history(line);
		line_count = count_lines_in_file(".minishell_history");
		if (line_count == -1)
		{
			perror("Error opening history file");
			close(fd);
			return ;
		}
		line_count++;
		ft_putnbr_fd(line_count, fd);
		ft_putstr_fd(". ", fd);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		close(fd);
	}
}
