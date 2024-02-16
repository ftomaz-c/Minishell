#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_tools
{
	char			**env;
	char			**path;
	char			*home;
	char			*user;
	char			*pwd;
	char			*oldpwd;
	int				pipes;
	bool			exit;
	struct s_lexer	*lexer;
	struct s_parser *parser;
}	t_tools;

typedef struct s_lexer
{
	char			*words;
	char			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

typedef struct	s_parser
{
	char			**str;
	int				(*builtin)(struct s_tools *, struct s_parser *);
	int				nb_redirections;
	char			*heredoc_limiter;
	t_lexer			*redirections;
	struct s_parser	*next;
	struct s_parser	*prev;
	
}	t_parser;

# endif