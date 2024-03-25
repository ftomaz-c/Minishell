#include "../../../includes/builtins.h"

/**
 * @brief Checks for invalid history options.
 * 
 * This function checks if the history command has 
 * * been provided with invalid options. 
 * If an invalid option is detected, it prints an error
 *  message and sets the exit status 
 * accordingly. Supported options include numeric
 *  arguments and too many arguments.
 * 
 * @param tools Pointer to tools structure.
 * @param command Pointer to parser structure containing
 *  parsed command.
 * 
 * @return Returns the exit status, which is 0 if no invalid 
 * options are detected, 
 * or EXIT_FAILURE if there are invalid options.
 * 
 * @note This function assumes that `tools` 
 * and `command` are valid pointers.
 * 
 * @warning None.
 * 
 * @see check_exit_args(), g_status, EXIT_FAILURE.
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * t_tools tools;
 * t_parser command;
 * int exit_status = invalid_history_options(&tools, &command);
 * ```
 */

int	invalid_history_options(t_tools *tools, t_parser *command)
{
	(void)tools;
	if (command->str[1])
	{
		if (!check_exit_args(command))
		{
			g_status = EXIT_FAILURE;
			printf("bash: history: %s: numeric argument required\n",
				command->str[1]);
			return (g_status);
		}
	}
	if (command->str[2] != NULL)
	{
		printf("bash: history: too many arguments\n");
		g_status = EXIT_FAILURE;
		return (g_status);
	}
	return (0);
}

/**
 * @brief Prints buffer lines based on specified size.
 * 
 * This function prints lines from a buffer based on the specified size.
 * 
 * @param buffer Pointer to the buffer containing lines to print.
 * @param size Size of lines to print.
 * @param i Index for iterating over buffer.
 * 
 * @return None.
 * 
 * @note This function assumes that `buffer` is a 
 * valid pointer containing line strings,
 * `size` is a positive integer representing the number of lines to print,
 * and `i` is an index within the valid range of the buffer.
 * 
 * @warning None.
 * 
 * @see ft_calloc(), ft_strdup(), print_buffer(), free_list().
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char **buffer;
 * int size = 10;
 * int i = 0;
 * get_buffer_lines_print(buffer, size, i);
 * ```
 */
void	get_buffer_lines_print(char **buffer, int size, int i)
{
	int		j;
	int		nlines;
	char	**new_buffer;

	nlines = 0;
	while (buffer[nlines])
		nlines++;
	if (size > nlines)
	{	
		size = nlines;
		j = 0;
	}
	else
		j = nlines - size;
	new_buffer = ft_calloc(sizeof(char **), size + 1);
	if (!new_buffer)
		return ;
	while (buffer[j])
	{
		new_buffer[i] = ft_strdup(buffer[j]);
		i++;
		j++;
	}
	print_buffer(new_buffer);
	free_list(new_buffer);
}

/**
 * @brief Retrieves history from file.
 * 
 * This function retrieves history from a specified
 *  file path and stores it in a buffer.
 * 
 * @param buffer Pointer to the buffer where history will be stored.
 * @param file_path Path to the history file.
 * 
 * @return Returns the buffer containing history 
 * if successful, otherwise NULL.
 * 
 * @note This function assumes that `buffer` is a 
 * valid pointer to store history lines,
 * and `file_path` is a valid string representing
 *  the path to the history file.
 * 
 * @warning None.
 * 
 * @see ft_calloc(), get_file_path_from_home(), open(), copy_buffer(), free().
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * char **buffer;
 * char *file_path = ".minishell_history";
 * buffer = get_history(buffer, file_path);
 * ```
 */

char	**get_history(char **buffer, char *file_path, int arg)
{
	int		fd;
	int		nlines;
	int		size;

	nlines = count_lines_in_file(file_path);
	size = 1;
	handle_history_sizes(&arg, &nlines, &size);
	buffer = ft_calloc(sizeof(char **), size + 1);
	if (!buffer)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: opening history file. History won't be stored\n");
		return (NULL);
	}
	copy_buffer(buffer, fd, nlines, arg);
	free(file_path);
	close(fd);
	return (buffer);
}

/**
 * @brief Executes the mini history command.
 * 
 * This function executes the mini history command,
 *  which prints a specified number 
 * of history lines or the entire history buffer if no argument is provided.
 * 
 * @param tools Pointer to tools structure.
 * @param command Pointer to parser structure containing parsed command.
 * 
 * @return Returns 0 on success, otherwise returns 1.
 * 
 * @note This function assumes that `tools` and `command` are valid pointers.
 * 
 * @warning None.
 * 
 * @see ft_atoi(), invalid_history_options(), 
 * get_history(), get_buffer_lines_print(), 
 * print_buffer(), free_list().
 * 
 * @example
 * 
 * ```
 * // Example usage:
 * t_tools tools;
 * t_parser command;
 * int exit_status = mini_history(&tools, &command);
 * ```
 */
int	cmd_history(t_tools *tools, t_parser *command)
{
	char	**buffer;

	(void)tools;
	buffer = NULL;
	if (command->str[1] && invalid_history_options(tools, command))
		return (1);
	if (command->str[1])
		buffer = get_history(buffer,
				get_file_path_from_home(tools->home, ".minishell_history"),
				ft_atoi(command->str[1]));
	else
		buffer = get_history(buffer,
				get_file_path_from_home(tools->home, ".minishell_history"), -1);
	print_buffer(buffer);
	free_list(buffer);
	return (0);
}
