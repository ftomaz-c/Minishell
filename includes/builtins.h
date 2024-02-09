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

#endif
