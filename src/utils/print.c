/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:07:27 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/**
 * @brief Prints the content of the lexer linked list.
 * 
 * This function prints the content of the lexer linked 
 * list, including index, words, and token.
 * 
 * @param tools Pointer to the tools struct containing 
 * the lexer linked list.
 */
void	print_lexer(t_tools *tools)
{
	t_lexer	*lexer;

	lexer = tools->lexer;
	printf("---------------------LEXER--------------------\n");
	printf("----------------------------------------------\n");
	while (lexer)
	{
		printf("index: %i\n", lexer->index);
		printf("words: %s\n", lexer->words);
		printf("token: %c\n", lexer->token);
		printf("----------------------------------------------\n");
		lexer = lexer->next;
	}
}

/**
 * @brief Prints the redirections stored in the parser structure.
 * 
 * This function prints the redirections stored in the parser structure,
 * including tokens and words associated with redirections.
 * 
 * @param parser A pointer to the parser structure containing redirections.
 */
void	print_parser_redirections(t_parser *parser)
{
	t_lexer	*redirections;

	redirections = parser->redirections;
	printf("redirections: ");
	while (redirections)
	{
		if (redirections->token)
			printf("%c ", redirections->token);
		else if (redirections->words)
			printf("%s ", redirections->words);
		redirections = redirections->next;
	}
}

/**
 * @brief Prints the content of the parser linked list.
 * 
 * This function prints the content of the parser linked 
 * list, including str, builtin, nb_redirections, 
 * heredoc_limiter, and redirections.
 * 
 * @param tools Pointer to the tools struct containing 
 * the parser linked list.
 */
void	print_parser(t_tools *tools)
{
	t_parser	*parser;
	int			i;

	parser = tools->parser;
	printf("--------------------PARSER--------------------\n");
	printf("----------------------------------------------\n");
	while (parser)
	{
		printf("str: ");
		i = 0;
		while (parser->str[i])
			printf(":%s:", parser->str[i++]);
		printf("\n");
		printf("builtin: %p\n", parser->builtin);
		printf("nb_redirections: %i\n", parser->nb_redirections);
		print_parser_redirections(parser);
		printf("\n");
		printf("----------------------------------------------\n");
		parser = parser->next;
	}
	printf("nb_pipes: %i\n", tools->pipes);
}
