#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	init_lexer(t_lexer *lexer)
{
	lexer->words = NULL;
	lexer->token = '\0';
	lexer->i = 0;
	lexer->next = NULL;
	lexer->pre = NULL;

}

int	exit_simple_error(char *msg)
{
	printf("%s\n", msg);
	return (0);
}
