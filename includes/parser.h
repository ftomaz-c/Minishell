/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/23 18:07:44 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*src/parser/parser.c*/
int			parse_words(t_parser *node, t_lexer *current);
t_lexer		*parse_tokens(t_parser *node, t_lexer *current, int *start);
int			get_command(t_parser *node, t_lexer *lexer, int *start, int end);
int			parse_lexer(t_parser **parser, t_lexer *lexer, int *start, int end);
int			parser(t_tools *tools);

/*src/parser/parser_redir.c*/
t_lexer		*add_redirection(t_lexer *current, t_parser *node, int *start);

/*src/parser/parser_utils.c*/
void		count_heredocs(t_parser *parser);
void		ft_lstadd_parser_back(t_parser**lst, t_parser *new);
void		free_parser(t_parser **parser);
t_parser	*init_parser(int start, int end);
t_lexer		*start_token(t_lexer *lexer, int start);

#endif