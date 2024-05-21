/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:26:46 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*src/builtins/builtins.c*/
int			(*is_builtin(char *str))(t_tools *tools, t_parser *parser);

/*src/builtins/cmd_cd/cmd_cd.c*/
int			cd_no_path(t_tools *tools, t_parser *command);
int			cd_handle_specific_path(t_tools *tools, t_parser *command);
int			cd_path(t_tools *tools, t_parser *command);
int			cmd_cd(t_tools *tools, t_parser *command);

/*src/builtins/cmd_cd/cmd_cd_utils.c*/
void		update_env_vars(t_tools *tools);
void		cd_err(int err, char *str, char root);
int			cd_handle_slash_path(t_tools *tools);
int			cd_handle_dot_path(t_tools *tools);

/*src/builtins/cmd_export/cmd_export.c*/
void		sort_print_env(t_tools *tools);
int			check_valid_export(char *parser);
void		export_variable_to_env(t_tools *tools, char *str);
int			check_if_var_exists(t_tools *tools, char *str);
int			cmd_export(t_tools *tools, t_parser *command);

/*src/builtins/cmd_export/cmd_export_utils1.c*/
void		copy_var_value_quotes(char *var_path, char *str, int start);
int			copy_var_name(char *var_path, char *str, int equal_pos);
char		*prepare_var(char *str);
char		**get_env_export(char **envp, int i);

/*src/builtins/cmd_export/cmd_export_utils2.c*/
int			check_var_path(char **env, char *var);
void		copy_var_value(char *var_path, char *str, int start);
void		get_new_var_value(char **var_value, char *str);
void		add_value_to_var(t_tools *tools, char *var_path, char *str);
void		substitute_env_var_value(t_tools *tools, char *var_path, char *str);

/*src/builtins/cmd_export/cmd_export_utils3.c*/
void		export_err(int err, char *str);
void		get_new_var(char **var, char *str);
int			copy_var_to_env(t_tools *tools, char **array,
				char *var_value, int i);

/*src/builtins/cmd_history/cmd_history.c*/
int			invalid_history_options(t_tools *tools, t_parser *command);
void		get_buffer_lines_print(char **buffer, int size, int i);
char		**get_history(char **buffer, char *file_path, int arg);
int			cmd_history(t_tools *tools, t_parser *command);

/*src/builtins/cmd_history/cmd_history_utils.c*/
void		handle_history_sizes(int *arg, int *nlines, int *size);
void		copy_buffer(char **buffer, int fd, int nlines, int arg);
void		print_buffer(char **str);

/*src/builtins/echo.c*/
int			echo_n_flag(char **str, int	*pos);
void		echo_print(t_parser *command, int pos, int flag);
int			cmd_echo(t_tools *tools, t_parser *command);

/*src/builtins/env.c*/
int			cmd_env(t_tools *tools, t_parser *command);

/*src/builtins/mini_exit.c*/
long long	check_if_within_range(char *status);
int			check_exit_args(t_parser *parser);
void		exit_err(int err, char *str);
int			cmd_exit(t_tools *tools, t_parser *parser);

/*src/builtins/pwd.c*/
int			cmd_pwd(t_tools *tools, t_parser *command);

/*src/builtins/unset.c*/
int			check_var(t_tools *tools, char *str);
void		unset_var_from_env(t_tools *tools, char *str, int i);
int			cmd_unset(t_tools *tools, t_parser *command);

#endif
