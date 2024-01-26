/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:43:46 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/26 14:48:44 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	}
	free(line);
	close (fd);
	return(count);
}

void    add_history_file(char *line)
{
	int	fd;
	int	line_count;
	
	fd = open(".minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening history file");
		return ;
	}
	add_history(line);
	line_count = count_lines_in_file(".minishell_history");
	if (line_count == -1)
	{
		perror("Error opening history file");
		close(fd);
		return ;
	}
	line_count++;
	ft_putnbr_fd(line_count, fd);
	ft_putstr_fd(". ", fd);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}