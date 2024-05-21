/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 20:14:09 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

/**
 * @brief Changes the current working directory to the user's home directory.
 * 
 * This function changes the current working directory
 *  to the user's home directory.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return 0 if the directory change is successful, 
 * otherwise prints an error message and returns 1.
 */
int	cd_no_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];
	char	*home_var;
	char	*env_var;

	(void)command;
	home_var = tools->home;
	env_var = get_var_from_env(tools->env, "HOME");
	if (!env_var)
		cd_err(4, command->str[1], 0);
	else if (ft_strcmp(tools->pwd, home_var) != 0)
	{
		if (chdir(home_var) == 0)
		{
			free(tools->oldpwd);
			tools->oldpwd = ft_strdup(tools->pwd);
			free(tools->pwd);
			tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
		}
	}
	free(env_var);
	return (0);
}

/**
 * @brief Handles changing the current working 
 * directory to a specific path.
 * 
 * This function handles changing the current working directory 
 * to a specific path provided as an argument.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return 0 if the directory change is successful, otherwise 
 * prints an error message and returns 1.
 */
int	cd_handle_specific_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];

	if (chdir(command->str[1]) == 0)
	{
		free(tools->oldpwd);
		tools->oldpwd = ft_strdup(tools->pwd);
		free(tools->pwd);
		tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
	}
	else if ((chdir(command->str[1]) < 0) && command->str[1][0])
		cd_err(errno, command->str[1], 0);
	return (g_status);
}

/**
 * @brief Handles changing the current working directory 
 * based on a provided path.
 * 
 * This function handles changing the current working
 * directory based on a provided path.
 * It supports changing to the parent directory ("..") and handling
 *  specific directory paths.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return 0 if the directory change is successful, otherwise
 *  prints an error message and returns 1.
 */
int	cd_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];

	if (ft_strcmp(command->str[1], "..") == 0)
	{
		if (chdir("..") == 0)
		{
			free(tools->oldpwd);
			tools->oldpwd = get_var_from_env(tools->env, "PWD");
			free(tools->pwd);
			tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
		}
		else
			cd_err(errno, command->str[1], 0);
	}
	else if (ft_strcmp(command->str[1], "-") == 0)
		cd_handle_slash_path(tools);
	else if (ft_strcmp(command->str[1], ".") == 0)
		cd_handle_dot_path(tools);
	else
		return (cd_handle_specific_path(tools, command));
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles the execution of the cd command, 
 * changing the current working directory.
 * 
 * This function handles the execution of the cd command, 
 * which changes the current working directory.
 * It supports changing to the home directory, parent 
 * directory (".."), and specific directory paths.
 * 
 * @param tools   Pointer to the tools struct containing 
 * necessary information.
 * @param command Pointer to the parser struct containing 
 * command information.
 * 
 * @return The global status after executing the cd command.
 */
int	cmd_cd(t_tools *tools, t_parser *command)
{
	if (command && command->str[0][0] == '/')
	{
		chdir(command->str[0]);
		cd_err(errno, command->str[0], '/');
		if (errno == 2)
			g_status = 127;
		else if (errno == 25)
			g_status = 126;
		if (errno == 0)
			chdir(tools->pwd);
	}
	else if ((command && !command->str[1])
		|| ft_strcmp(command->str[1], "~") == 0)
		cd_no_path(tools, command);
	else if (command && command->str[1] && !command->str[2])
		cd_path(tools, command);
	else
		cd_err(1, NULL, 0);
	update_env_vars(tools);
	return (g_status);
}
