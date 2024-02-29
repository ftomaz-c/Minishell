#include "../../includes/minishell.h"

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

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	return (i);
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
		// while (line && !history_section(line))
		// {
		// 	free(line);
		// 	line = get_next_line(fd);
		// }
	}
	free(line);
	close (fd);
	return (count);
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
 * @brief Constructs a file path by appending a file name 
 * to the user's home directory path.
 * 
 * This function constructs a file path by concatenating
 *  the user's home directory path
 * obtained from the HOME environment variable with
 *  the provided file name.
 * 
 * @param file_name The name of the file to append to
 * the home directory path.
 * 
 * @return A dynamically allocated string containing the 
 * constructed file path.
 *         The caller is responsible for freeing the memory 
 * allocated for the string.
 *         Returns NULL if memory allocation fails or if the
 *  HOME environment variable is not set.
 * 
 * @note The caller must free the memory allocated for the 
 * returned string after use to avoid memory leaks.
 * @note This function relies on the ft_strjoin function to concatenate strings.
 * @note Assumes that the HOME environment variable is set
 *  to the user's home directory path.
 * 
 * @warning If memory allocation fails or if the HOME
 *  environment variable is not set,
 *          this function returns NULL without modifying errno.
 * 
 * @see ft_strjoin
 * 
 * @example
 * 
 * ```
 * // Example usage of the function
 * char *file_path = get_file_path_from_home("example.txt");
 * if (file_path) {
 *     // Use the file_path
 *     printf("File path: %s\n", file_path);
 *     // Free the memory allocated for the file path when no longer needed
 *     free(file_path);
 * } else {
 *     // Handle error: unable to retrieve file path
 *     fprintf(stderr, "Error: Failed to retrieve file path.\n");
 * }
 * ```
 */

char	*get_file_path_from_home(char *file_name)
{
	char	*home_var;
	char	*tmp;

	home_var = ft_strjoin(getenv("HOME"), "/");
	if (!home_var)
		return (NULL);
	tmp = ft_strjoin(home_var, file_name);
	if (!tmp)
		return (NULL);
	free(home_var);
	return (tmp);
}
