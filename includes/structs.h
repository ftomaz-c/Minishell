/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/22 16:19:04 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char			*name;
	int				pipes;
	int				exit;
	int				nprompts;
	int				nint_mode;
	int				line_count;
	char			**lines;
	int				token_flag;
	int				original_stdin;
	int				original_stdout;
	struct s_lexer	*lexer;
	struct s_parser	*parser;
}	t_tools;

typedef struct s_lexer
{
	char			*words;
	char			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*pre;
}	t_lexer;

typedef struct s_parser
{
	char			**str;
	int				(*builtin)(struct s_tools *, struct s_parser *);
	int				nb_redirections;
	char			*stdin_file_name;
	char			*stdout_file_name;
	int				stdin_flag;
	int				stdout_flag;
	int				fd_err;
	char			*delimiter;
	int				fd[2];
	int				stdout_backup_fd;
	t_lexer			*redirections;
	struct s_parser	*next;
	struct s_parser	*prev;	
}	t_parser;

typedef struct s_expander
{
	char			**split;
	int				size;
	int				index;
	int				start;
}	t_expander;

typedef struct s_builtin
{
	char	*name;
	int		(*builtin)(t_tools *, t_parser *);
}	t_builtin;

#endif
