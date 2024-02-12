#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	update_history(".minishell_history");
	error_check(argc, argv);
	tools.exit = false;
	tools.env = get_env(envp);
	while (tools.exit != true)
	{
		if (!config_tools(&tools))
		{
			printf ("Error: Failed to allocate memory for tools\n");
			free_tools(&tools);
			exit (EXIT_FAILURE);
		}
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
			
			//print_lexer(&tools);

			if (!parse_lexer(&tools))
			{
				free(line);
				free_tools(&tools);
				free_parser(&tools.parser);
				free_tools(&tools);
				return (1);
			}
			
			// print_parser(&tools);

			if (tools.parser->builtin)
				execute_builtin(&tools);
			free_parser(&tools.parser);
			free_lexer(&tools.lexer);
		}
		else
			printf("Error: input with unclosed quotes\n");
		free(line);
		free_tools(&tools);
		
	}
	return (0);
}
