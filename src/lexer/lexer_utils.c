#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

void init_lexer(t_lexer **lexer)
{
	*lexer = malloc(sizeof(t_lexer));
	if (*lexer == NULL) {
		// Handle allocation failure
		return;
	}
	(*lexer)->words = NULL;
	(*lexer)->token = '\0';
	(*lexer)->next = NULL;
	(*lexer)->pre = NULL;
}

int	exit_simple_error(char *msg)
{
	printf("%s\n", msg);
	return (0);
}
void	ft_lstaddback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
