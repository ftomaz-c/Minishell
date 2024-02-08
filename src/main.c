#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	// t_lexer	*lexer;
	t_tools	tools;

	update_history();
	error_check(argc, argv);
	while (1)
	{
		if (!config_tools(&tools, envp))
		{
			printf ("Error: Failed to allocate memory for tools\n");
			free_tools(&tools);
			exit (EXIT_FAILURE);
		}
		printf("old dir: %s Cur dir: %s\n", tools.oldpwd, tools.pwd);
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		// add_history_file(line);
		// if (!lex_line(line, &lexer))
		// {
		// 	free(line);
		// 	return (1);
		// }
// ------------------------------------
// ------    Test pwd ------------------
// ------------------------------------
		if (!ft_strncmp(line, "pwd", ft_strlen(line)))
			pwd();

// ------------------------------------
// ------    Test cd ------------------
// ------------------------------------

		char	**cdchr = malloc(3 * sizeof(char *));
		char	*t;
		
		cdchr[0] = "cd";
		cdchr[1] = "/hoe";
		cdchr[2] = NULL;
		// cdchr[1] = "/ome";
		// // cdchr[2] = NULL;
		t = NULL;
		if (!ft_strncmp(line, "cd", ft_strlen(line)))
			cd(t, cdchr);

// ------------------------------------
// ------------------------------------
		// printf("old dir: %s Cur dir: %s\n", tools.oldpwd, tools.pwd);
		free_tools(&tools);
		// free_lexer(&lexer);
		free(line);
	}
	return (0);
}
