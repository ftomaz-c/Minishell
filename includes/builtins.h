#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*builtins/builtins.c*/
int		(*is_builtin(char *str))(t_tools *tools, t_parser *parser);

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
int		export(t_tools *tools, t_parser *command);
int	    check_if_var_exists(t_tools *tools, char *str);
void	export_variable_to_env(t_tools *tools, char *str);
int	    check_valid_export(char *parser);
void	sort_print_env(t_tools *tools);

/*builtins/export_utils1.c*/
char	**get_env_export(char **envp, int i);
char	*prepare_var(char *str);
void	copy_var_name(char *var_path, char *str, int equal_pos);
void	copy_var_value_quotes(char *var_path, char *str, int start);
void	sort_array(char **env_copy);

/*builtins/export_utils2.c*/
void	substitute_env_var_value(t_tools *tools, char *var_path, char *str);
void	get_new_var_value(char **var_value, char *str);
void	copy_var_value(char *var_path, char *str, int start);
int		check_var_path(char **env, char *var);

/*builtins/export_utils3.c*/
int		copy_var_to_env(t_tools *tools, char **new_array, char *var_value, int i);
void	get_new_var(char **var, char *str);
void	copy_var(char *var_path, char *str);
int		find_char_position(char *str, char c);
int		ft_isalpha_plus_underscore(int c);

/*builtins/unset.c*/
int		unset(t_tools *tools, t_parser *command);
int 	check_var(t_tools *tools, char *str);
void	unset_var_from_env(t_tools *tools, char *str, int i);
int		count_lines(char **list);

/*builtins/unset.c*/
int		unset(t_tools *tools, t_parser *command);

#endif
