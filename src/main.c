#include "../includes/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char	*line;

	update_history(".minishell_history");
	error_check(argc, argv);
	if (!config_tools(&tools, envp))
	{
		ft_putstr_fd("Error: Failed to allocate memory for tools\n", STDERR_FILENO);
		free_tools(&tools);
		exit (EXIT_FAILURE);
	}
	while (1)
	{
		//line = prompt_line(&tools);
		line = readline(".minishell: ");
		minishell(&tools, line);
		free(line);
		if (tools.exit)
			break ;
	}
	free_tools(&tools);
	exit (g_status);
}
