#include "../includes/minishell.h"

void	print_lexer(t_tools *tools)
{
	t_lexer *lexer = tools->lexer;

	printf("---------------------LEXER--------------------\n");
	printf("----------------------------------------------\n");
	while (lexer)
	{
		printf("index: %i\n", lexer->index);
		printf("words: %s\n", lexer->words);
		printf("token: %c\n", lexer->token);
		printf("----------------------------------------------\n");
		lexer = lexer->next;
	}
}

void	print_parser(t_tools *tools)
{
	t_parser	*parser = tools->parser;
	int			i;

	printf("--------------------PARSER--------------------\n");
	printf("----------------------------------------------\n");
	while (parser)
	{
		printf("str: ");
		i = 0;
		while(parser->str[i])
			printf("%s ", parser->str[i++]);
		printf("\n");
		printf("builtin: %p\n", parser->builtin);
		printf("nb_redirections: %i\n", parser->nb_redirections);
		printf("heredoc_limiter: %s\n", parser->heredoc_limiter);
		
		t_lexer *redirections = parser->redirections;
		printf("redirections: ");
		while (redirections)
		{
			if (redirections->token)
				printf("%c ", redirections->token);
			else if (redirections->words)
				printf("%s ", redirections->words);
			redirections = redirections->next;
		}
		printf("\n");
		
		printf("----------------------------------------------\n");
		parser = parser->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tools	tools;

	update_history();
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
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		add_history_file(line);
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

		//print_parser(&tools);
		
		free(line);
		free_parser(&tools.parser);
		free_tools(&tools);
	}
	return (0);
}
