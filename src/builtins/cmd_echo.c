/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/27 19:35:40 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/**
 * @brief Determines if the echo command has the -n flag.
 * 
 * This function checks if the echo command has the -n flag
 * and returns the length of the flag if present.
 * 
 * @param str Pointer to the array of command arguments.
 * @param pos Pointer to the position in the command arguments array.
 * 
 * @return The length of the flag if present, 0 otherwise.
 */
int	echo_n_flag(char **str, int	*pos)
{
	size_t	i;

	if (!str[2])
		return (0);
	i = 0;
	while (str[*pos] != NULL && ft_strncmp(str[*pos], "-n", 2) == 0)
	{
		i = 1;
		while (str[*pos][i] && str[*pos][i] != ' ' && str[*pos][i] == 'n')
			i++;
		if (*pos != 1 && str[*pos][i] != '\0')
			return (i);
		else if (*pos == 1 && str[*pos][i] != '\0')
			return (0);
		(*pos)++;
	}
	return (i);
}

/**
 * @brief Prints the arguments of the echo command.
 * 
 * This function prints the arguments of the echo command
 * with proper spacing and handles the -n flag if present.
 * 
 * @param command Pointer to the parsed echo command.
 * @param pos The position in the command arguments array.
 * @param flag The length of the -n flag if present, 0 otherwise.
 */
void	echo_print(t_parser *command, int pos, int flag)
{
	while (command->str[pos])
	{
		ft_putstr_fd(command->str[pos], STDOUT_FILENO);
		if (command->str[pos + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		pos++;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

/**
 * @brief Executes the echo command.
 * 
 * This function executes the echo command by printing its arguments.
 * If no arguments are provided, it prints a newline character.
 * If the -n flag is present, it omits the trailing newline.
 * 
 * @param tools Pointer to the tools structure.
 * @param command Pointer to the parsed echo command.
 * 
 * @return The exit status of the command (EXIT_SUCCESS).
 */
int	cmd_echo(t_tools *tools, t_parser *command)
{
	int			i;
	int			flag;
	t_parser	*cmd;

	i = 1;
	(void)tools;
	cmd = command;
	if (!cmd->str[i])
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
	{
		flag = echo_n_flag(cmd->str, &i);
		echo_print(cmd, i, flag);
	}
	global_status()->nbr = EXIT_SUCCESS;
	return (global_status()->nbr);
}
