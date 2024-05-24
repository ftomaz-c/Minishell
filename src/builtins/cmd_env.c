/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/23 17:38:35 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/**
 * @brief Handles the arguments for the env command.
 * 
 * This function checks if the first argument of the env command
 * is "-i". If it is, it sets the exit status to EXIT_SUCCESS
 * and returns. If not, it prints an error message indicating
 * that the specified file or directory does not exist and sets
 * the exit status to 127.
 * 
 * @param command Pointer to the parsed env command.
 */
void	env_args(t_tools *tools, t_parser *command)
{
	char	*cmd_args[2];

	if (ft_strcmp(command->str[1], "-i") == 0)
	{
		cmd_args[0] = command->str[2];
		cmd_args[1] = NULL;
		exec_path(tools, cmd_args, basic_env());
		free_and_exit(tools, global_status()->nbr);
		global_status()->nbr = EXIT_SUCCESS;
		return ;
	}
	ft_putstr_fd("env: '", STDOUT_FILENO);
	ft_putstr_fd(command->str[1], STDOUT_FILENO);
	ft_putstr_fd("'", STDOUT_FILENO);
	ft_putstr_fd(": no such file or directory\n", STDOUT_FILENO);
	global_status()->nbr = 127;
}

/**
 * @brief Prints the environment variables.
 * 
 * This function prints the environment variables to the standard output.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the env command.
 */
int	cmd_env(t_tools *tools, t_parser *command)
{
	int		i;
	t_tools	*tmp;

	i = 0;
	if (command->str[1])
	{
		env_args(tools, command);
		return (global_status()->nbr);
	}
	tmp = tools;
	while (tmp->env[i])
	{
		if (!ft_strchr(tmp->env[i], '='))
			i++;
		else
		{
			if (!tmp->env[i])
				break ;
			ft_putstr_fd(tmp->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			i++;
		}
	}
	global_status()->nbr = EXIT_SUCCESS;
	return (global_status()->nbr);
}
