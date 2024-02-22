#include "../includes/minishell.h"

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
		line = prompt_line(&tools);
		add_history_file(line, ".minishell_history");
		if (check_unclosed_quotes(line))
		{
			if (!lex_line(line, &tools))
			{
				free(line);
				free_tools(&tools);
				return (1);
			}
			
			// print_lexer(&tools);

			if (!parser(&tools))
			{
				free(line);
				free_lexer(&tools.lexer);
				free_parser(&tools.parser);
				free_tools(&tools);
				return (1);
			}
			
			// print_parser(&tools);

			executor(&tools);
			free_parser(&tools.parser);
			free_lexer(&tools.lexer);
		}
		else
			printf("Error: input with unclosed quotes\n");
		free(line);
		if (tools.exit)
			break;
	}
	free_tools(&tools);
	return (0);
}
