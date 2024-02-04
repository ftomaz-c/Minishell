/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:43:46 by ftomazc           #+#    #+#             */
/*   Updated: 2024/02/04 16:17:18 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Writes a line to a history file, appending it with a line count.
 * 
 * This function writes a given line to a history file specified by the file descriptor.
 * It appends the line with a line count, preceded by a period and space.
 * If the history file cannot be opened, it prints an error message and closes the file descriptor.
 * 
 * @param line The line to write to the history file.
 * @param fd The file descriptor of the history file.
 * 
 * @note This function assumes that the history file exists and is writable.
 * @note The line count is incremented by one for each new line added to the history file.
 * 
 * @warning If the history file cannot be opened, this function will print an error message and return without writing anything.
 * 
 * @see count_lines_in_file & add_history_file
 * 
 * @example
 * 
 * ```
 * // Example usage of the function
 * int history_fd = open(".minishell_history", O_WRONLY | O_APPEND);
 * if (history_fd == -1) {
 *     // Handle error opening history file
 * }
 * write_in_history_file("command", history_fd);
 * close(history_fd);
 * ```
 */ 

void	write_in_history_file(char *line, int fd)
{
	int	line_count;

	line_count = count_lines_in_file(".minishell_history");
	if (line_count == -1)
	{
		perror("Error opening history file");
		close(fd);
		return ;
	}
	if (line_count != 0)
		ft_putchar_fd('\n', fd);
	line_count++;
	ft_putnbr_fd(line_count, fd);
	ft_putstr_fd(". ", fd);
	ft_putstr_fd(line, fd);
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

void    add_history_file(char *line)
{
	int	fd;
	
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
		write_in_history_file(line, fd);
		close(fd);
	}
}

/**
 * @brief Appends a section of a line to the history_line.
 * 
 * This function appends a section of a line to the history_line.
 * If the new line is NULL, it allocates memory for an empty string.
 * It then finds the index of the history section in the line, and appends the
 * section starting from that index to the new line. Finally, it frees the old
 * new line and returns the updated new line.
 * 
 * @param line The line from which to extract the history section.
 * @param new_line The current state of the new line being built for history.
 * 
 * @return char* The updated new line with the history section appended.
 * 
 * @note This function assumes that the `ft_strdup()` and `ft_strjoin()` functions
 *       are available for string manipulation. It also assumes that the
 *       `history_section()` function is available to find the index of the history
 *       section in a line.
 * 
 * @warning The returned pointer points to dynamically allocated memory. It is the
 *          caller's responsibility to free this memory when it is no longer needed
 *          to prevent memory leaks.
 */

char	*append_section_to_history(char *line, char *new_line)
{
	char	*tmp;
	int		i;
	
	if (new_line == NULL)
		new_line = ft_strdup("");
	i = history_section(line);
	tmp = ft_strjoin(new_line, line + i);
	free(new_line);
	return(tmp);
}

/**
 * @brief Adds a line to the history.
 * 
 * This function adds a line to the history if it contains a history section
 * or if the line is NULL. It removes the newline character from the end of
 * the line if it exists, adds the line to the history, frees the memory
 * allocated for the line, and sets the new line pointer to NULL.
 * 
 * @param line The line to add to the history.
 * @param new_line The line being built for history.
 * 
 * @return char* The updated new line pointer.
 * 
 * @note This function assumes that the `ft_strlen()` function is available for
 *       string length calculation and that the `add_history()` function is available
 *       to add a line to the history.
 * 
 * @warning This function modifies the `new_line` parameter by removing the newline
 *          character if it exists. If the `new_line` parameter is NULL or not properly
 *          allocated, it may result in undefined behavior.
 */

char	*add_section_to_history(char *line, char *new_line)
{
	if (history_section(line) || line == NULL)
	{
		if (new_line[ft_strlen(new_line) - 1] == '\n')
   			new_line[ft_strlen(new_line) - 1] = '\0';
		add_history(new_line);
		free(new_line);
		new_line = NULL;
	}
	return (new_line);
}

/**
 * @brief Updates the history with lines processed.
 * 
 * This function updates the history with lines processed. It reads lines from
 * the ".minishell_history" file, processes each line to extract the history
 * section, adds the section to the new line being built, and adds the line to
 * the history if it contains a history section or if it is NULL. Finally, it
 * closes the file and frees the memory allocated for the lines.
 * 
 * @note This function relies on the `process_section()` function to extract the
 *       history section from each line and the `get_next_line()` function to read
 *       lines from the file.
 * 
 * @warning This function assumes that the ".minishell_history" file exists and can
 *          be opened for reading. Failure to open the file may result in errors or
 *          unexpected behavior.
 */

void	update_history(void)
{
	char	*line;
	int		fd;
	char	*new_line;

	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
	{
		perror("Error: opening history\n");
		return ;
	}
	line = get_next_line(fd);
	new_line = NULL;
	while(line)
	{
		new_line = append_section_to_history(line, new_line);
		free(line);
		line = get_next_line(fd);
		new_line = add_section_to_history(line, new_line);
	}
	free(line);
	close(fd);
}
