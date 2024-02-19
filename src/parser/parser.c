#include "../../includes/parser.h"

/**
 * @brief Parses words from the lexer and stores them in the parser node.
 * 
 * This function parses words from the lexer and stores them in the parser node. If the node's
 * 'builtin' flag is not set, it checks if the current word is a built-in command. It then
 * duplicates the word and stores it in the parser node's 'str' array.
 * 
 * @param node A pointer to the parser node.
 * @param current A pointer to the current lexer node.
 * @param i The index to store the word in the parser node's 'str' array.
 * 
 * @return Returns 1 on success, 0 on failure.
 * 
 * @note This function assumes that 'node' and 'current' are valid pointers.
 * 
 * @warning Memory allocated for the duplicated word should be freed if the function fails.
 */

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

/**
 * @brief Parses redirection tokens from the lexer and updates the parser node.
 * 
 * This function parses redirection tokens from the lexer and updates the parser node
 * accordingly. It counts the number of redirections encountered and adds redirection nodes
 * to the parser node's 'redirections' linked list.
 * 
 * @param node A pointer to the parser node.
 * @param current A pointer to the current lexer node.
 * 
 * @return Returns 1 if redirection tokens are parsed, 0 otherwise. Returns -1 on failure.
 * 
 * @note This function assumes that 'node' and 'current' are valid pointers.
 * 
 * @warning Memory allocated for the redirection node should be freed if the function fails.
 */

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

/**
 * @brief Parses the command from the lexer and updates the parser node.
 * 
 * This function parses the command from the lexer and updates the parser node accordingly.
 * It iterates through the lexer nodes between 'start' and 'end', parsing words and tokens.
 * 
 * @param node A pointer to the parser node.
 * @param lexer A pointer to the lexer.
 * @param start The starting index in the lexer.
 * @param end The ending index in the lexer.
 * 
 * @note This function assumes that 'node' and 'lexer' are valid pointers.
 */

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

/**
 * @brief Parses the lexer and creates parser nodes for each command.
 * 
 * This function parses the lexer and creates parser nodes for each command separated by pipes.
 * It initializes a parser node, calls get_command() to parse the command, and adds the node
 * to the parser linked list.
 * 
 * @param parser A double pointer to the parser linked list.
 * @param lexer A pointer to the lexer.
 * @param start The starting index in the lexer.
 * @param end The ending index in the lexer.
 * 
 * @return Returns 1 on success, 0 on failure.
 * 
 * @note This function assumes that 'parser' and 'lexer' are valid pointers.
 * 
 * @warning Memory allocated for the parser node should be freed if the function fails.
 */

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

/**
 * @brief Parses the input tools.lexer and creates parser nodes for each command.
 * 
 * This function parses the input tools (lexer) and creates parser nodes for each command.
 * It iterates through the lexer nodes, detecting pipes to separate commands, and calls
 * parse_lexer() to create parser nodes.
 * 
 * @param tools A pointer to the input tools containing lexer and parser information.
 * 
 * @return Returns 1 on success, 0 on failure.
 * 
 * @note This function assumes that 'tools' is a valid pointer.
 */

int	parser(t_tools *tools)
{
	t_lexer	*current;
	int		start;
	int		end;

	tools->parser = NULL;
	if (!tools->lexer)
		return (1);
	current = tools->lexer;
	start = current->index;
	while (current)
	{
		end = current->index;
		if (current->token == '|' || current->next == NULL)
		{
			if (current->next == NULL)
				end++;
			else
				tools->pipes++;
			if (!parse_lexer(&tools->parser, tools->lexer, start, end))
				return (0);
			start = current->index;
		}
		current = current->next;
	}
	return (1);
}
