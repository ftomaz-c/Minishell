#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		parse_lexer(t_tools *tools);
void	free_parser(t_parser **parser);

#endif