#include "../../includes/builtins.h"

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
 * 
 * @note This function assumes that `buffer` is a valid 
 * pointer to store lines,
 * `fd` is a valid file descriptor for reading, and 
 * `nlines` is a positive integer.
 * 
 * @warning None.
 * 
 * @see get_next_line(), ft_strdup(), free().
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char **buffer;
 * int fd = open("file.txt", O_RDONLY);
 * int nlines = 10;
 * copy_buffer(buffer, fd, nlines);
 * ```
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
 * 
 * @note This function assumes that `str` is a
 *  valid pointer to an array of strings
 * where each string represents a line to print.
 * 
 * @warning None.
 * 
 * @see None.
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char **buffer;
 * print_buffer(buffer);
 * ```
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
