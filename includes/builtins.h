#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*src/builtins/builtins.c*/
int		(*is_builtin(char *str))(t_tools *tools, t_parser *parser);

/*src/builtins/cd.c*/
void	update_env_vars(t_tools *tools);
int		cd_no_path(t_tools *tools, t_parser *command);
int		cd_handle_specific_path(t_tools *tools, t_parser *command);
int		cd_path(t_tools *tools, t_parser *command);
int		cmd_cd(t_tools *tools, t_parser *command);

/*src/builtins/env.c*/
int		cmd_env(t_tools *tools, t_parser *command);

/*src/builtins/pwd.c*/
int		cmd_pwd(t_tools *tools, t_parser *command);

/*src/builtins/echo.c*/
void	echo_print(t_parser *command, int pos, int flag);
int		cmd_echo(t_tools *tools, t_parser *command);

/*src/builtins/mini_exit.c*/
int		check_exit_args(t_parser *parser);
int		cmd_exit(t_tools *tools, t_parser *parser);

/*src/builtins/export.c*/
void	sort_print_env(t_tools *tools);
int		check_valid_export(char *parser);
void	export_variable_to_env(t_tools *tools, char *str);
int		check_if_var_exists(t_tools *tools, char *str);
int		cmd_export(t_tools *tools, t_parser *command);

/*src/builtins/export_utils1.c*/
void	sort_array(char **env_copy);
void	copy_var_value_quotes(char *var_path, char *str, int start);
int		copy_var_name(char *var_path, char *str, int equal_pos);
char	*prepare_var(char *str);
char	**get_env_export(char **envp, int i);

/*src/builtins/export_utils2.c*/
int		check_var_path(char **env, char *var);
void	copy_var_value(char *var_path, char *str, int start);
void	get_new_var_value(char **var_value, char *str);
void	substitute_env_var_value(t_tools *tools, char *var_path, char *str);
void	add_value_to_var(t_tools *tools, char *var_path, char *str);

/*src/builtins/export_utils3.c*/
int		ft_isalpha_plus_underscore(int c);
int		find_char_position(char *str, char c);
void	copy_var(char *var_path, char *str);
void	get_new_var(char **var, char *str);
int		copy_var_to_env(t_tools *tools, char **array, char *var_value, int i);

/*src/builtins/unset.c*/
int		count_lines(char **list);
int		check_var(t_tools *tools, char *str);
void	unset_var_from_env(t_tools *tools, char *str, int i);
int		cmd_unset(t_tools *tools, t_parser *command);

/*src/builtins/mini_history.c*/
int		invalid_history_options(t_tools *tools, t_parser *command);
void	get_buffer_lines_print(char **buffer, int size, int i);
char	**get_history(char **buffer, char *file_path, int arg);
int		cmd_history(t_tools *tools, t_parser *command);

/*src/builtins/mini_history_utils.c*/
void	copy_buffer(char **buffer, int fd, int nlines, int arg);
void	print_buffer(char **str);

#endif
