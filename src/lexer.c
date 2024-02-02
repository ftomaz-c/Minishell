
#include "../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	init_lexer(t_lexer *lexer)
{
	lexer->words = NULL;
	lexer->token = NULL;
	lexer->i = 0;
	lexer->next = NULL;
	lexer->pre = NULL;

}

int	exit_simple_error(char *msg)
{
	printf("%s\n", msg);
	return (0);
}

int	lex_line(char *line, t_lexer *lexer, char **envp)
{
	char	**line_split_quotes;

	init_lexer(lexer);
	line_split_quotes = ft_split_quotes(line, ' '); // splits quotes considering the quotes present
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
