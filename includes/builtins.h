#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*builtins/builtins.c*/
void	execute_builtin(t_tools *tools);

/*builtins/cd.c*/
void	update_env_vars(t_tools *tools);
int		cd_no_path(t_tools *tools, t_parser *command);
int		cd_handle_specific_path(t_tools *tools, t_parser *command);
int		cd_path(t_tools *tools, t_parser *command);
int		cd(t_tools *tools, t_parser *command);

/*builtins/env.c*/
int		env(t_tools *tools, t_parser *command);

/*builtins/pwd.c*/
int		pwd(t_tools *tools, t_parser *command);

/*builtins/echo.c*/
int		echo(t_tools *tools, t_parser *command);

/*builtins/mini_exit.c*/
int		mini_exit(t_tools *tools, t_parser *parser);

/*builtins/export.c*/
int		export(t_tools *tools, t_parser *parser);
void	free_env(char **str);
void	sort_array(char **env_copy);
int		find_char_position(char *str, char c);
void	copy_var_name(char *var_path, char *str, int equal_pos);
char	**get_env_export(char **envp, int i);
char	*prepare_var(char *str);
void	substitute_env_var_value(t_tools *tools, char *var_path, char *str);
void	copy_var_name(char *var_path, char *str, int equal_pos);
int		find_char_position(char *str, char c);

int		check_var_path(char **env, char *var);
int		ft_isalpha_plus_underscore(int c);
void	get_new_var_value(char **var_value, char *str);
void	get_new_var(char **var, char *str);
int	    copy_var_to_env(t_tools *tools, char **new_array, char *var_value, int i);

/*builtins/unset.c*/
int	unset(t_tools *tools, t_parser *command);
int	count_lines(char **list);

#endif
