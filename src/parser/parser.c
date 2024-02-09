#include "../../includes/parser.h"

int	export(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	unset(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	mini_exit(t_tools *tools, t_parser *parser)
{
	(void)tools;
	(void)parser;
	return(0);
}

int	(*is_builtin(char *str))(t_tools *tools, t_parser *parser)
{
	static struct {
		char	*name;
		int		(*builtin)(t_tools *, t_parser *);
    } builtin_array[] = {
        {"echo", echo},
        {"cd", cd},
        {"pwd", pwd},
        {"export", export},
        {"unset", unset},
        {"env", env},
        {"exit", mini_exit}
    };
	size_t		i;

	i = 0;
	while (i < (sizeof(builtin_array) / sizeof(builtin_array[0])))
	{
		if (ft_strncmp(builtin_array[i].name, str, ft_strlen(builtin_array[i].name)) == 0)
			return (builtin_array[i].builtin);
		i++;
	}
	return (NULL);
}

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
		if (current->redirections != NULL)
			free_lexer(&current->redirections);
		free(current);
		current = next;
	}
	*parser = NULL;
}

int	get_command(t_parser **parser, t_lexer *lexer, int start, int end)
{
	t_parser	*node;
	t_lexer		*redirections_node;
	t_lexer		*current;
	int			i;

	node = ft_calloc(1, sizeof (t_parser));
	if (!node)
		return (0);
	node->str = ft_calloc(end - start + 1, sizeof(char *));
	if (!node->str)
	{
		free(node);
		return (0);
	}
	i = 0;
	current = lexer;
	while (current->index != start)
		current = current->next;
	while (start < end)
	{
		if (current->words)
		{
			if (!node->builtin)
				node->builtin = is_builtin(current->words);
			node->str[i] = ft_strdup(current->words);
			if (!node->str[i])
			{
				free_parser(&node);
				return (0);
			}
			i++;
		}
		else if (current->token)
		{
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
						return (0);
					}
					redirections_node->index = current->index;
					redirections_node->token = current->token;
					if (current->words)
						redirections_node->words = ft_strdup(current->words);
					ft_lstaddback(&node->redirections, redirections_node);
					current = current->next;
				}
				break;
			}
		}
		start++;
		current = current->next;
	}
	ft_lstadd_parser_back(parser, node);
	return (1);
}

int	parse_lexer(t_tools *tools)
{
	t_lexer	*current;
	int		start;
	int		end;

	tools->pipes = 0;
	tools->parser = NULL;
	current = tools->lexer;
	start = current->index;
	end = 0;
	while (current)
	{
		end = current->index;
		if (current->token == '|' || current->next == NULL)
		{
			if (current->next == NULL)
				end++;
			if (!get_command(&tools->parser, tools->lexer, start, end))
				return (0);
			tools->pipes++;
			start = current->index;
		}
		current = current->next;
	}
	return (1);
}
