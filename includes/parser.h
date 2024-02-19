#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*parser.c*/
int			parse_words(t_parser *node, t_lexer *current, int *i);
int			parse_tokens(t_parser *node, t_lexer *current);
void		get_command(t_parser *node, t_lexer *lexer, int start, int end);
int			parse_lexer(t_parser **parser, t_lexer *lexer, int start, int end);
int			parser(t_tools *tools);

/*parser_utils.c*/
void		free_strlist(char **str);
void		ft_lstadd_parser_back(t_parser**lst, t_parser *new);
void		free_parser(t_parser **parser);
t_parser	*init_parser(int start, int end);
t_lexer		*start_token(t_lexer *lexer, int start);

#endif