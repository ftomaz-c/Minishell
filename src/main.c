#include "../includes/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char	*line;

	config_tools(&tools, envp);
	update_history(&tools, ".minishell_history");
	error_check(argc, argv);
	while (1)
	{
		handle_sigaction(react_sig_handler);
		if (!isatty(STDIN_FILENO))
		{
			ft_putstr_fd(".minishell: ", STDOUT_FILENO);
			line = get_next_line(1);
			if (line)
			{
				char *newline = ft_calloc(sizeof(char *), ft_strlen_nl(line));
				ft_memcpy(newline, line, ft_strlen_nl(line));
				if (newline)
				{
					free(line);
					line = newline;
				}
			}
		}
		else
			line = readline(".minishell: ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDIN_FILENO);
			break ;
		}
		minishell(&tools, line);
		free(line);
		if (tools.exit)
			break ;
	}
	free_and_exit(&tools);
}
