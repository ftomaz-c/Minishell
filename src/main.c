#include "../includes/minishell.h"

int	g_status = 0;


int main(int argc, char **argv, char **envp)
{
	t_tools tools;
	char *line;
	int n;
	int i;
	char **lines = NULL;

	lines = ft_calloc(sizeof(char **), 1024);
	config_tools(&tools, envp);
	update_history(&tools, ".minishell_history");
	error_check(argc, argv);
	n = 0;
	while (1)
	{
		handle_sigaction(react_sig_handler);
		if (!isatty(STDIN_FILENO))
		{
			tools.gnl = 1;
			line = get_next_line(0);
			while (line)
			{
				lines[n] = ft_strdup(ft_strtrim(line, "\n"));
				n++;
				free(line);
				line = get_next_line(0);
			}
			i = 0;
			while (i < n)
			{
				minishell(&tools, lines[i]);
				free(lines[i]);
				i++;
			}
			free(lines);
			break;
		}
		else 
		{
			line = readline(".minishell: ");
			if (!line)
			{
				ft_putstr_fd("exit\n", STDIN_FILENO);
				break;
			}
			minishell(&tools, line);
			free(line);
			if (tools.exit)
				break;
		}
	}
	free_and_exit(&tools);
	return 0;
}