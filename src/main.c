/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:37:33 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/26 13:19:28 by ftomazc          ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (line && *line)
			add_history_file(line);
		free(line);   
	}
	return (0);
}