#include "../../includes/minishell.h"

/**
 * @brief Counts the occurrences of a character in a string.
 * 
 * This function counts the occurrences of a specified character in a given string.
 * 
 * @param line Pointer to the string in which to search for occurrences.
 * @param c The character to count occurrences of.
 * 
 * @return Returns the number of occurrences of the character in the string.
 * 
 * @note This function assumes that `line` points to a valid null-terminated string.
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
 * @param line_array Pointer to the array of strings where lines will be stored.
 * @param line Pointer to the string to be treated and split into lines.
 * 
 * @return None.
 * 
 * @note This function assumes that `line_array` is a valid pointer to store 
 * an array of strings representing lines, and `line` is a valid null-terminated string.
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
