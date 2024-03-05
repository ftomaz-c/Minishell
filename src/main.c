#include "../includes/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	update_history(".minishell_history");
	error_check(argc, argv);
	if (!config_tools(&tools, envp))
	{
		printf ("Error: Failed to allocate memory for tools\n");
		free_tools(&tools);
		exit (EXIT_FAILURE);
	}
	while (1)
	{
		//line = prompt_line(&tools);
		line = readline(".minishell: ");
		add_history_file(line, ".minishell_history");
		if (check_unclosed_quotes(line))
		{
			if (!lex_line(line, &tools))
			{
				free(line);
				// free_tools(&tools);
				free_lexer(&tools.lexer);
				// g_status = 2;
				continue ;
			}
			// print_lexer(&tools);

			parser(&tools);

			// print_parser(&tools);

			if (tools.lexer)
				free_lexer(&tools.lexer);
			if (tools.parser)
			{
				executor(&tools);
				free_parser(&tools.parser);
			}
		}
		else
			printf("Error: input with unclosed quotes\n");
		free(line);
		if (tools.exit)
			break ;
	}
	free_tools(&tools);
	exit (g_status);
}
