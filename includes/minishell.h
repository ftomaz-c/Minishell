#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "structs.h"
# include "lexer.h"
# include "parser.h"

/*tools.c*/
int		config_tools(t_tools *tools);
char	**get_env(char **envp);
char	**get_path(char **env);
char 	*get_var_from_env(char **env, char *var);
void	free_tools(t_tools *tools);

/*error.c*/
void	error_check(int argc, char **argv);

/*history.c*/
void	write_in_history_file(char *line, int fd);
void    add_history_file(char *line);
void	update_history(void);
void	add_history_file(char *line);
void	append_to_history(char *line);

/*history_utils.c*/
int 	count_lines_in_file(const char *filename);
int		history_section(char *line);


/*utils/print.c*/
void	print_lexer(t_tools *tools);
void	print_parser(t_tools *tools);

/*Builtins.c*/
// int	pwd(t_tools *tools, t_parser **command);
int	pwd();

// int	cd(t_tools *tools, t_parser *command);
int	cd(char *tools, char **command);

#endif
