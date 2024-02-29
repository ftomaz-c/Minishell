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
int	mini_history(t_tools *tools, t_parser *command)
{
	int		fd;
	char	*file_path;
	char	*line;
	// char	**buffer
	// int		size;

	(void)tools;
	(void)command;
	if (command->str[1] && invalid_history_options(tools, command))
		return (1);
	// if (command->str[1])
	// 	size = ft_atoi(command->str[1]);
	
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
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	free(file_path);
	close(fd);
	return (0);
}
