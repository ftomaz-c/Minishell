#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 199309L

# include <unistd.h>
# include "../libft/includes/libft.h"
# include "structs.h"
# include "utils.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "executor.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <dirent.h>

// extern int	global_status;
extern int	g_status;

/*src/minishell/minishell.c*/
void	minishell(t_tools *tools, char *line);

/*src/minishell/signals.c*/
void	ignore_sig_handler(int sig);
void	react_sig_handler(int sig);
void	handle_sigaction(void (*handler)(int));

void	sig_handler(int sig);

/*src/minishell/tools.c*/
void	handle_shlvl(char *pre_lvl, char **new_lvl, size_t lvl);
void	update_env(t_tools *tools);
void	config_tools(t_tools *tools, char **envp);

/*src/minishell/tools_utils1.c*/
int		compare_var_to_env(char *env, char *var);
void	free_tools(t_tools *tools);
char	**get_path(t_tools *tools, char **env);
char	*get_pwd(t_tools *tools, char **env);

/*src/minishell/tools_utils2.c*/
void	remove_whoami(char **env, char *user);
void	get_whoami(char **env);
char	*get_home_from_etc_passwd(char *line);
char	*get_source_home_var(t_tools *tools, char *str);

#endif
