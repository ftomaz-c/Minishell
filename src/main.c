#include "../includes/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char	*line;

	config_tools(&tools, envp);
	update_history(".minishell_history");
	error_check(argc, argv);
	handle_sigaction();
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
