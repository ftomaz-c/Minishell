#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	error_check(argc, argv);
	while (1)
	{
		if (!config_tools(&tools, envp))
		{
			printf ("Error: Failed to allocate memory for tools\n");
			free_tools(&tools);
			exit (EXIT_FAILURE);
		}
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		add_history_file(line);
		free_tools(&tools);
		free(line);
	}
	return (0);
}
