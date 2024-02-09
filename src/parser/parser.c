#include "../../includes/parser.h"

int	parse_words(t_parser *node, t_lexer *current, int *i)
{
	if (!node->builtin)
		node->builtin = is_builtin(current->words);
	node->str[*i] = ft_strdup(current->words);
	if (!node->str[*i])
	{
		free_parser(&node);
		return (0);
	}
	(*i)++;
	return (1);
}

int	parse_tokens(t_parser *node, t_lexer *current)
{
	t_lexer		*redirections_node;

	if (current->token == '>' || current->token == '<')
	{
		while (current && current->token != '|')
		{
			if (current->token == '>' || current->token == '<')
				node->nb_redirections++;
			redirections_node = ft_calloc(1, sizeof(t_lexer));
			if (!redirections_node)
			{
				free_parser(&node);
				return (-1);
			}
			redirections_node->index = current->index;
			redirections_node->token = current->token;
			if (current->words)
				redirections_node->words = ft_strdup(current->words);
			ft_lstaddback(&node->redirections, redirections_node);
			current = current->next;
		}
		return (1);
	}
	return (0);
}

void	get_command(t_parser *node, t_lexer *lexer, int start, int end)
{
	t_lexer		*current;
	int			token;
	int			i;

	current = start_token(lexer, start);
	i = 0;
	while (start < end)
	{
		if (current->words)
		{
			if (!parse_words(node, current, &i))
				return ;
		}
		else if (current->token)
		{
			token = parse_tokens(node, current);
			if (token == -1)
				return ;
			else if (token == 1)
				break;
		}
		start++;
		current = current->next;
	}
	return ;
}

int	parse_lexer(t_parser **parser, t_lexer *lexer, int start, int end)
{
	t_parser	*node;

	node = init_parser(start, end);
	if (!node)
		return (0);
	get_command(node, lexer, start, end);
	ft_lstadd_parser_back(parser, node);
	return (1);
}

int	parser(t_tools *tools)
{
	t_lexer	*current;
	int		start;
	int		end;

	tools->pipes = 0;
	tools->parser = NULL;
	current = tools->lexer;
	start = current->index;
	while (current)
	{
		end = current->index;
		if (current->token == '|' || current->next == NULL)
		{
			if (current->next == NULL)
				end++;
			if (!parse_lexer(&tools->parser, tools->lexer, start, end))
				return (0);
			tools->pipes++;
			start = current->index;
		}
		current = current->next;
	}
	return (1);
}
