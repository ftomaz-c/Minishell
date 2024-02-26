#include "../../includes/builtins.h"

int	mini_history(t_tools *tools, t_parser *command)
{
	int		fd;
	char	*file_path;
	char	*line;

	(void)tools;
	(void)command;
	file_path = get_file_path_from_home(".minishell_history");
	if (!file_path)
	{
		perror("Error: Failed to retrieve history\n");
		return (1);
	}
	printf("file_path: %s\n", file_path);
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
