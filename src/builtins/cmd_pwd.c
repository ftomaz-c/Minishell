/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/23 17:39:50 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
/**
 * @brief Prints the current working directory.
 * 
 * This function prints the current working directory to the standard output.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the pwd command.
 */
int	cmd_pwd(t_tools *tools, t_parser *command)
{
	char	buf[1024];

	(void)tools;
	(void)command;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		free(tools->pwd);
		free(tools->oldpwd);
		tools->pwd = get_var_from_env(tools->env, "PWD");
		tools->oldpwd = get_var_from_env(tools->env, "OLDPWD");
		ft_strcpy(buf, tools->pwd);
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	global_status()->nbr = EXIT_SUCCESS;
	return (global_status()->nbr);
}
