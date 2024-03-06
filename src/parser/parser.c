#include "../../includes/parser.h"

/**
 * @brief Parses words from the lexer and stores 
 * them in the parser node.
 * 
 * This function parses words from the lexer and stores
 * them in the parser node. If the node's
 * 'builtin' flag is not set, it checks if the current
 * word is a built-in command. It then
 * duplicates the word and stores it in the parser
 * node's 'str' array.
 * 
 * @param node A pointer to the parser node.
 * @param current A pointer to the current lexer node.
 * @param i The index to store the word in the 
 * parser node's 'str' array.
 * 
 * @return Returns 1 on success, 0 on failure.
 * 
 * @note This function assumes that 'node' and
 * 'current' are valid pointers.
 * 
 * @warning Memory allocated for the duplicated word 
 * should be freed if the function fails.
 */

int	parse_words(t_parser *node, t_lexer *current)
{
	int	i;

	i = 0;
	if (!node->builtin)
		node->builtin = is_builtin(current->words);
	while (node->str[i])
		i++;
	node->str[i] = ft_strdup(current->words);
	if (!node->str[i])
	{
		free_parser(&node);
		return (0);
	}
	return (1);
}

/**
 * @brief Parses redirection tokens from the lexer
 * and updates the parser node.
 * 
 * This function parses redirection tokens from the
 * lexer and updates the parser node
 * accordingly. It counts the number of redirections 
 * encountered and adds redirection nodes
 * to the parser node's 'redirections' linked list.
 * 
 * @param node A pointer to the parser node.
 * @param current A pointer to the current lexer node.
 * 
 * @return Returns 1 if redirection tokens are parsed, 0 
 * otherwise. Returns -1 on failure.
 * 
 * @note This function assumes that 'node' and 'current' 
 * are valid pointers.
 * 
 * @warning Memory allocated for the redirection node 
 * should be freed if the function fails.
 */

t_lexer	*parse_tokens(t_parser *node, t_lexer *current, int *start)
{
	if (current->token == '>' || current->token == '<' 
	|| ft_isdigit(current->token) || current->token == '&')
	{
		if (ft_isdigit(current->token) || current->token == '&')
			current = add_redirection(current, node, start);
		node->nb_redirections++;
		current = add_redirection(current, node, NULL);
		if (current && (current->token == '<' || current->token == '>'))
			current = add_redirection(current, node, start);
		if (current && current->words)
			current = add_redirection(current, node, start);
		if (!current->next && (current->token == '<' || current->token == '>'))
		{
			syntax_err(current->token);
			return (NULL);
		}
	}
	return (current);
}

/**
 * @brief Parses the command from the lexer and 
 * updates the parser node.
 * 
 * This function parses the command from the lexer and 
 * updates the parser node accordingly.
 * It iterates through the lexer nodes between 'start' and 
 * 'end', parsing words and tokens.
 * 
 * @param node A pointer to the parser node.
 * @param lexer A pointer to the lexer.
 * @param start The starting index in the lexer.
 * @param end The ending index in the lexer.
 * 
 * @note This function assumes that 'node' and 'lexer'
 *  are valid pointers.
 */

int	get_command(t_parser *node, t_lexer *lexer, int *start, int end)
{
	t_lexer		*current;

	current = start_token(lexer, *start);
	while (*start < end)
	{
		if (current->words)
		{
			if (!parse_words(node, current))
				return (0);
			current = current->next;
		}
		else if (current->token)
		{
			current = parse_tokens(node, current, start);
			if (current == NULL)
				return (0);
		}
		(*start)++;
	}
	return (1);
}

/**
 * @brief Parses the lexer and creates parser nodes 
 * for each command.
 * 
 * This function parses the lexer and creates parser
 *  nodes for each command separated by pipes.
 * It initializes a parser node, calls get_command() to
 * parse the command, and adds the node
 * to the parser linked list.
 * 
 * @param parser A double pointer to the parser linked list.
 * @param lexer A pointer to the lexer.
 * @param start The starting index in the lexer.
 * @param end The ending index in the lexer.
 * 
 * @return Returns 1 on success, 0 on failure.
 * 
 * @note This function assumes that 'parser' and 'lexer' 
 * are valid pointers.
 * 
 * @warning Memory allocated for the parser node should
 *  be freed if the function fails.
 */

int	parse_lexer(t_parser **parser, t_lexer *lexer, int *start, int end)
{
	t_parser	*node;

	node = init_parser(*start, end);
	if (!node)
		return (0);
	if (!get_command(node, lexer, start, end))
	{
		free_lexer(&node->redirections);
		free_parser(&node);
		free_parser(parser);
		return (0);
	}
	ft_lstadd_parser_back(parser, node);
	return (1);
}

/**
 * @brief Parses the input tools.lexer and creates 
 * parser nodes for each command.
 * 
 * This function parses the input tools (lexer) and creates
 *  parser nodes for each command.
 * It iterates through the lexer nodes, detecting pipes 
 * to separate commands, and calls
 * parse_lexer() to create parser nodes.
 * 
 * @param tools A pointer to the input tools containing 
 * lexer and parser information.
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

	if (!tools->lexer)
		return (1);
	tools->parser = NULL;
	current = tools->lexer;
	start = current->index;
	while (current)
	{
		if (current->token == '|' || current->next == NULL)
		{
			end = current->index;
			if (current->next == NULL)
				end++;
			else
				tools->pipes++;
			if (!parse_lexer(&tools->parser, tools->lexer, &start, end))
				return (0);
			start++;
		}
		current = current->next;
	}
	return (1);
}
