#include "../../includes/minishell.h"

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
 * 
 * @note This function assumes that `line_array` is a valid pointer to store 
 * an array of strings representing lines, and
 *  `line` is a valid null-terminated string.
 * 
 * @warning None.
 * 
 * @see ft_calloc(), ft_substr(), ft_strlen(), find_next_char_position().
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char **line_array;
 * char *line = "Hello\nWorld\n";
 * treat_line(&line_array, line);
 * ```
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
 * 
 * @note This function assumes that `line_array` is a valid 
 * pointer to a dynamically allocated array of strings.
 * 
 * @warning This function assumes that `line` and `file_path` 
 * are valid pointers and that `fd` is a valid file descriptor.
 * 
 * @see add_history, treat_line, write_in_history_file, free_list
 * 
 * @example
 * ```
 * // Example usage:
 * char *line = "example line";
 * char **line_array = NULL;
 * int fd = open("history.txt", O_WRONLY | O_APPEND);
 * char *file_path = "history.txt";
 * 
 * add_line(line, &line_array, fd, file_path);
 * ```
 */

void	add_line(char *line, char ***line_array, int fd, char *file_path)
{
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
 * 
 * @note This function is typically used after reading 
 * lines from a history file to verify its integrity.
 * 
 * @warning This function assumes that `fd` is a valid file descriptor.
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