#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	update_history(".minishell_history");
	error_check(argc, argv);
	tools.env = get_env(envp);
	while (1)
	{
		if (!config_tools(&tools))
		{
			printf ("Error: Failed to allocate memory for tools\n");
			free_tools(&tools);
			exit (EXIT_FAILURE);
		}
		line = prompt_line(&tools);
		add_history_file(line, ".minishell_history");
		if (!lex_line(line, &tools))
		{
			free(line);
			free_tools(&tools);
			return (1);
		}
		
		print_lexer(&tools);

		if (!parser(&tools))
		{
			free(line);
			free_lexer(&tools.lexer);
			free_parser(&tools.parser);
			free_tools(&tools);
			return (1);
		}

		print_parser(&tools);

		free(line);
		free_lexer(&tools.lexer);
		free_parser(&tools.parser);
		free_tools(&tools);
	}
	return (0);
}
