#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	update_history();
	error_check(argc, argv);
	tools.env = get_env(envp);
	tools.pwd = NULL;
	while (1)
	{
		if (!config_tools(&tools))
		{
			printf ("Error: Failed to allocate memory for tools\n");
			free_tools(&tools);
			exit (EXIT_FAILURE);
		}	
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		// add_history_file(line);
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
		
		// // print_parser(&tools);

		if (tools.parser->builtin)
			execute_builtin(&tools);
		
		free(line);
		free_lexer(&tools.lexer);
		free_parser(&tools.parser);
		free_tools(&tools);
		
	}
	return (0);
}
