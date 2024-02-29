#include "../../includes/builtins.h"

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

void	get_buffer_lines_print(char **buffer, int size)
{
	int		i;
	int		j;
	int		nlines;
	char	**new_buffer;

	i = 0;
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

int	mini_history(t_tools *tools, t_parser *command)
{
	int		fd;
	char	*file_path;
	char	*line;
	char	**buffer = NULL;
	int		size;
	int		nlines;
	int		i;

	(void)tools;
	(void)command;
	if (command->str[1] && invalid_history_options(tools, command))
		return (1);
	if (command->str[1])
		size = ft_atoi(command->str[1]);
	nlines = count_lines_in_file(".minishell_history");
	buffer = ft_calloc(sizeof(char **), nlines + 1);
	if (!buffer)
		return (-1);

	file_path = get_file_path_from_home(".minishell_history");
	if (!file_path)
	{
		perror("Error: Failed to retrieve history\n");
		return (1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: opening history file. History won't be stored\n");
		return (1);
	}
	i = 0;
	line = get_next_line(fd);
	while (line && i < nlines)
	{
		buffer[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(file_path);
	close(fd);
	if (command->str[1])	
		get_buffer_lines_print(buffer, size);
	else
		print_buffer(buffer);
	free_list(buffer);
	return (0);
}


