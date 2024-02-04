#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "lexer.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_tools
{
	char	**env;
	char	**path;
	char	*pwd;
	char	*oldpwd;
}	t_tools;

/*tools.c*/
int		config_tools(t_tools *tools, char **envp);
char	**get_env(char **envp);
char	**get_path(char **env);
char	*get_var_from_env(char **envp, char *var);
void	free_tools(t_tools *tools);

/*error.c*/
void	error_check(int argc, char **argv);

/*history.c*/
void	add_history_file(char *line);
int		count_lines_in_file(const char *filename);
void	write_in_history_file(char *line, int fd);

#endif
