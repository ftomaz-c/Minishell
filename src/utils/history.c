/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/23 18:18:08 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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
 */
void	write_in_history_file(char **line, int fd, char *file_path)
{
	int		line_count;
	int		i;

	line_count = count_lines_in_file(file_path);
	i = 0;
	if (!check_line_count(line_count, fd))
	{
		close(fd);
		return ;
	}
	while (line[i])
	{
		if (!check_empty_line(line[i]))
			i++;
		else
		{
			line_count++;
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(line_count, fd);
			ft_putstr_fd("  ", fd);
			ft_putstr_fd(line[i], fd);
			i++;
		}
	}
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
 */
void	add_history_file(t_tools *tools, char *line, char *file_name)
{
	int		fd;
	char	*file_path;
	char	**line_array;

	line_array = NULL;
	if (line == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(global_status()->nbr);
	}
	file_path = get_file_path_from_home(tools->home, file_name);
	if (!file_path)
		perror("Error: Failed to retrieve file path. History wont be stored\n");
	if (line && *line)
	{
		fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("Error: opening history file. History won't be stored\n");
			return ;
		}
		add_line(line, &line_array, fd, file_path);
		close(fd);
	}
	free(file_path);
}

/**
 * @brief Appends a line to the history section.
 * 
 * This function appends a line to the history section,
 * removing any leading section marker.
 * It ensures that the line added to the history does not 
 * end with a newline character.
 * 
 * @param line The line to be appended to the history.
 * 
 * @return void
 */
void	append_to_history(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	i = history_section(line);
	new_line = ft_substr(line, i, ft_strlen_nl(line) - i);
	j = 0;
	while (new_line[j] != '\n' && new_line[j])
		j++;
	if (new_line[j] == '\n')
		new_line[j] = '\0';
	add_history(new_line);
	free(new_line);
}

/**
 * @brief Updates the history with lines processed.
 * 
 * This function updates the history with lines 
 * processed by reading lines from
 * the ".minishell_history" file, processing each
 *  line to extract the history
 * section, and adding the section to the new line being
 * built. If the line contains
 * a history section or if it is NULL, it adds the line to 
 * the history. Finally, it
 * closes the file and frees the memory allocated for the lines.
 * 
 * @note This function relies on the `append_to_history()`
 *  function to add lines
 *       to the history and the `get_next_line()` function 
 * to read lines from the file.
 */
void	update_history(t_tools *tools, char *file_name)
{
	char	*line;
	char	*file_path;
	int		fd;

	file_path = get_file_path_from_home(tools->home, file_name);
	if (!file_path)
		return ;
	if (access(file_path, F_OK))
	{
		free(file_path);
		return ;
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		append_to_history(line);
		free(line);
		line = get_next_line(fd);
	}
	free(file_path);
	free(line);
	close(fd);
}
