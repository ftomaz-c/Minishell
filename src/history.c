#include "../includes/minishell.h"

/**
 * @brief Writes a line to a history file, appending it with a line count.
 * 
 * This function writes a given line to a history file specified
 * by the file descriptor.
 * It appends the line with a line count, preceded by a period and space.
 * If the history file cannot be opened, it prints an error message and
 * closes the file descriptor.
 * 
 * @param line The line to write to the history file.
 * @param fd The file descriptor of the history file.
 * 
 * @note This function assumes that the history file exists and is writable.
 * @note The line count is incremented by one for each new line added
 * to the history file.
 * 
 * @warning If the history file cannot be opened, this function will
 * print an error message and return without writing anything.
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
 * This function appends the provided line to the history
 * file ".minishell_history",
 * along with the current line count followed by a period and space.
 * It also updates the line count by reading the current number of
 * lines in the history file.
 * 
 * @param line The line to be added to the history file. This should
 * be a null-terminated string
 *             obtained from the readline function or similar. The
 * function does not modify the contents of the string.
 * 
 * @note The function assumes that ".minishell_history" exists
 * in the current directory.
 *       If the file does not exist, it will be created.
 *       The function also assumes that the provided line is properly
 * formatted and does not contain newline characters,
 *       as newline characters will be automatically appended to the line when
 * written to the file.
 *       If the file or line cannot be processed, appropriate error messages 
 * will be printed to stderr.
 *       Ensure that the file has appropriate permissions for writing.
 *       The function may allocate additional memory temporarily while
 * reading the file.
 * 
 * @warning This function does not handle concurrent access to the history file.
 * If multiple instances of the program
 *           attempt to write to the history file simultaneously,
 * unexpected behavior
 * may occur.
 * 
 * @see count_lines_in_file
 */

void	add_history_file(char *line)
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
 * @brief Appends a line to the history section.
 * 
 * This function appends a line to the history section, removing any leading section marker.
 * It ensures that the line added to the history does not end with a newline character.
 * 
 * @param line The line to be appended to the history.
 * 
 * @return void
 * 
 * @note This function assumes that the history_section function determines the starting index of the actual command in the line.
 * @note Assumes that the add_history function is available and handles the addition of the line to the history.
 * @note Assumes that ft_substr and ft_strlen functions are available to manipulate strings.
 * 
 * @warning It's the responsibility of the caller to ensure that the input line is properly formatted and does not exceed memory bounds.
 * 
 * @see history_section, add_history, ft_substr, ft_strlen
 * 
 * @example
 * 
 */

void	append_to_history(char *line)
{
	char *new_line;
	int	i;
	int	j;

	i = history_section(line);
	new_line = ft_substr(line, i, ft_strlen(line) - i);
	j = 0;
	while(new_line[j] != '\n' && new_line[j])
		j++;
	if (new_line[j] == '\n')
		new_line[j] = '\0';
	add_history(new_line);
	free(new_line);
}

/**
 * @brief Updates the history with lines processed.
 * 
 * This function updates the history with lines processed by reading lines from
 * the ".minishell_history" file, processing each line to extract the history
 * section, and adding the section to the new line being built. If the line contains
 * a history section or if it is NULL, it adds the line to the history. Finally, it
 * closes the file and frees the memory allocated for the lines.
 * 
 * @note This function relies on the `append_to_history()` function to add lines
 *       to the history and the `get_next_line()` function to read lines from the file.
 * 
 * @warning This function assumes that the ".minishell_history" file exists and can
 *          be opened for reading. Failure to open the file may result in errors or
 *          unexpected behavior.
 * 
 * @see append_to_history, get_next_line
 * 
 * @example
 * 
 * ```
 * // Example usage of update_history function
 * update_history();
 * // Updates the command history with lines from ".minishell_history" file
 * ```
 */


void	update_history(void)
{
	char	*line;
	int		fd;

	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
	{
		perror("Error: opening history\n");
		return ;
	}
	line = get_next_line(fd);
	while(line)
	{
		append_to_history(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
