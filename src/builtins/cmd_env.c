/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 13:26:31 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/**
 * @brief Handles the execution of the 'env' command with arguments.
 * 
 * This function processes the arguments passed to the 'env' command.
 * If the first argument is "-i", it sets up a minimal environment and 
 * executes a simple command. Otherwise, it prints an error message
 * indicating an invalid option.
 * 
 * @param tools Pointer to a t_tools structure containing necessary
 *  tools and settings.
 * @param command Pointer to a t_parser structure containing the parsed 
 * command and its arguments.
 */
void	env_args(t_tools *tools, t_parser *command)
{
	char	**b_env;

	if (ft_strcmp(command->str[1], "-i") == 0)
	{
		if (command->str[2])
		{
			b_env = calloc (sizeof(char *), 2);
			b_env[0] = ft_strdup("_=/bin/env");
			execute_simple_cmd(tools, command, b_env);
			free_list(b_env);
		}
		global_status()->nbr = EXIT_SUCCESS;
	}
	else
	{
		ft_putstr_fd("env: invalid option -- '", STDERR_FILENO);
		ft_putstr_fd(command->str[1], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		global_status()->nbr = 125;
	}
}

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
int	validate_env(t_tools *tools, t_parser *command)
{
	char	*value;

	value = get_var_from_env(tools->env, "PATH");
	if (!value)
	{
		ft_putstr_fd("minishell: env: no such file or directory\n",
			STDOUT_FILENO);
		global_status()->nbr = 127;
		return (1);
	}
	else if (command->str[1])
	{
		env_args(tools, command);
		free(value);
		return (1);
	}
	free(value);
	return (0);
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
	if (validate_env(tools, command))
		return (global_status()->nbr);
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
