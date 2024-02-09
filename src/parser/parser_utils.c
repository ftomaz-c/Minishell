#include "../../includes/parser.h"

void	free_strlist(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_lstadd_parser_back(t_parser**lst, t_parser *new)
{
	t_parser	*last;

	if (!new)
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
	new->prev = last;
}

void	free_parser(t_parser **parser)
{
	t_parser	*current;
	t_parser	*next;

	current = *parser;
	if (!parser && *parser == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		if (current->str != NULL)
			free_strlist(current->str);
		if (current->redirections)
			free_lexer(&current->redirections);
		free(current);
		current = next;
	}
	*parser = NULL;
}

t_parser	*init_parser(int start, int end)
{
	t_parser	*node;

	node = ft_calloc(1, sizeof (t_parser));
	if (!node)
		return (NULL);
	node->str = ft_calloc(end - start + 1, sizeof(char *));
	if (!node->str)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_lexer	*start_token(t_lexer *lexer, int start)
{
	t_lexer		*current;

	current = lexer;
	while (current->index != start)
		current = current->next;
	return (current);
}