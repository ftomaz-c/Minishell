#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	init_lexer(t_lexer **lexer)
{
	*lexer = malloc(sizeof(t_lexer));
	if (*lexer == NULL)
		return ;
	(*lexer)->words = NULL;
	(*lexer)->token = '\0';
	(*lexer)->index = 0;
	(*lexer)->next = NULL;
	(*lexer)->pre = NULL;
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

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*current;
	t_lexer	*next;

	current = *lexer;
	if (*lexer == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		free(current->words);
		free(current);
		current = next;
	}
	*lexer = NULL;
}

void	free_list(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
