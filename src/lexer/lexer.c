
#include "../../includes/minishell.h"

int	lex_line(char *line, t_lexer *lexer, char **envp)
{
	char	**line_split_quotes;

	init_lexer(lexer);
	line_split_quotes = lexer_split(line, ' '); // splits quotes considering the quotes present
	// line_split_tokens = 
	// add_line_to_lexer_struct(line_split, lexer); // next step -> separate words from the tokens found
	
	// 					Uncomment section bellow to see splitted line
	expander(line_split_quotes, envp);
	int	i = 0;
	while (line_split_quotes[i])
	{
		printf("word: %s\n", line_split_quotes[i]);
		free(line_split_quotes[i]);
		i++;
	}
	free(line_split_quotes);
	return (1);
}
