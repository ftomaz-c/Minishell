#include "../../includes/utils.h"

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
 * @brief Adds a new node to the end of a lexer list.
 * 
 * This function adds the lexer node 'new' to the end of the
 * lexer list pointed by 'lst'.
 * 
 * @param lst Pointer to the pointer to the head of the lexer list.
 * @param new Pointer to the new lexer node to be added.
 * 
 * @note This function assumes that 'lst' is a valid pointer to a
 * pointer to a lexer list,
 *       and 'new' is a valid pointer to a lexer node.
 * 
 * @warning The function does not perform input validation on 'lst' or 'new'.
 *          It may result in unexpected behavior if 'lst' or 'new' is NULL.
 * 
 * @example
 * ```
 * t_lexer *lst = NULL;
 * t_lexer *new_node = malloc(sizeof(t_lexer));
 * ft_lstaddback(&lst, new_node);
 * // 'new_node' will be added to the end of the lexer list 'lst'
 * ```
 */

void	ft_lstaddback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->pre = last;
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
 * @brief Frees the memory allocated for a null-terminated array of strings.
 * 
 * This function frees the memory allocated for each string in the array 'list',
 * as well as the memory allocated for the array itself.
 * 
 * @param list Pointer to the array of strings to free.
 * 
 * @note This function assumes that 'list' is a null-terminated array of strings.
 * 
 * @warning The function does not perform input validation on 'list'.
 *          It may result in unexpected behavior if 'list' is NULL
 * or if any of its elements are NULL.
 * 
 * @example
 * ```
 * char *list[] = {"Hello", "world", NULL};
 * free_list(list);
 * // All memory allocated for the array 'list' and its strings will be freed
 * ```
 */

void	free_list(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}