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
		while (line && !history_section(line))
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	free(line);
	close (fd);
	return(count);
}

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
 * 
 * @note This function assumes that the `ft_isdigit()` function is available to
 *       check if a character is a digit.
 * 
 * @warning The returned index is based on a zero-based index. If the history
 *          section is not found, or if the line is NULL or empty, the function
 *          returns 0.
 */

int		history_section(char *line)
{
	int	i;

	i = 0;
	if (line == NULL || *line == '\0')
        return 0;
	while (ft_isdigit(line[i]))
	{
		if (line[i] == '\0')
			return (0);
		i++;
	}
	if (line[i] == '.')
		return (i + 2);
	return (0);
}