#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h> // For boolean type


/*tools.c*/
int		config_tools(t_tools *tools, char **envp);
char	**get_env(char **envp);
char	**get_path(char **env);
char	*get_var_from_env(char **env, char *var);
void	free_tools(t_tools *tools);

/*error.c*/
void	error_check(int argc, char **argv);

/*prompt.c*/
char	**handle_home_abreviation(t_tools *tools, char **str);
char	**generate_prompt(t_tools *tools);
char	*prompt_line(t_tools *tools);

/*history.c*/
void	write_in_history_file(char *line, int fd, char *file_path);
void    add_history_file(char *line, char *file_name);
void	update_history(char *file_name);
void	append_to_history(char *line);

/*history_utils.c*/
int 	count_lines_in_file(const char *filename);
int		history_section(char *line);
char	*get_file_path_from_home(char *file_name);

/*utils/print.c*/
void	print_lexer(t_tools *tools);
void	print_parser(t_tools *tools);

#endif
