#ifndef STRUCTS_H
# define STRUCTS_H

# define LESS 1
# define LESS_LESS 2
# define GREAT 3
# define GREAT_GREAT 4 

typedef struct s_tools
{
	char			**env;
	char			**path;
	char			*home;
	char			*user;
	char			*pwd;
	char			*oldpwd;
	int				pipes;
	int				exit;
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
	char			*stdin_file_name;
	char			*stdout_file_name;
	int				stdin_flag;
	int				stdout_flag;	
	t_lexer			*redirections;
	struct s_parser	*next;
	struct s_parser	*prev;	
}	t_parser;

# endif