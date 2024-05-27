/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/27 17:30:14 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/**
 * @brief Checks if the given status string is within the range 
 * of a long long integer.
 * 
 * This function converts the status string to a long long integer
 * using ft_atoll().
 * If the conversion results in an error due to overflow or underflow, it sets
 * the errno to ERANGE and returns 0. Otherwise, it returns the converted number.
 * 
 * @param status The status string to be converted.
 * @return The converted long long integer, or 0 if out of range.
 */
long long	check_if_within_range(char *status)
{
	long long	nbr;

	nbr = ft_atoll(status);
	if (errno == ERANGE)
		nbr = 0;
	return (nbr);
}

/**
 * @brief Checks if the argument provided to 
 * the exit command is a valid integer.
 * 
 * This function checks if the argument provided to 
 * the exit command is a valid integer.
 * It verifies each character of the argument to 
 * ensure it consists only of digits.
 * 
 * @param parser Pointer to the parser struct 
 * containing command information.
 * 
 * @return 1 if the argument is a valid integer, 0 otherwise.
 */
int	check_exit_args(t_parser *parser)
{
	int	is_zero;
	int	j;

	j = 0;
	is_zero = 0;
	while (ft_isspace(parser->str[1][j]))
		j++;
	if (!parser->str[1][j])
		return (0);
	if (parser->str[1][j] == '+' || parser->str[1][j] == '-')
		j++;
	if (parser->str[1][j] == '-' && !parser->str[1][j + 1])
		return (2);
	while (ft_isdigit(parser->str[1][j]))
		j++;
	if (j != 0 && parser->str[1][j - 1] == '0')
		is_zero = 1;
	while (ft_isspace(parser->str[1][j]))
		j++;
	if (parser->str[1][j])
		return (0);
	if (!check_if_within_range(parser->str[1]) && !is_zero)
		return (0);
	return (1);
}

/**
 * @brief Handles the execution of the exit command.
 * 
 * This function handles the execution of the exit
 *  command, which terminates the shell.
 * It validates the argument provided to the exit 
 * command and updates the global status accordingly.
 * 
 * @param tools  Pointer to the tools struct containing necessary information.
 * @param parser Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the exit command.
 */
void	exit_err(int err, char *str)
{
	if (err == 1)
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		if (ft_strcmp(str, "exit") != 0)
		{
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	}
	else if (err == 2)
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		if (ft_strcmp(str, "exit") != 0)
		{
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
	}
}

/**
 * @brief Handles the exit command.
 * 
 * This function processes the exit command by checking for
 * valid arguments and setting the exit status accordingly.
 * If no argument is provided, it sets the exit status to
 * EXIT_SUCCESS. If an argument is provided, it checks if
 * it is a valid integer. If it is not a valid integer or
 * if multiple arguments are provided, it sets the exit status
 * to 2 and prints an error message. If the argument is a
 * valid integer, it sets the exit status to that value.
 * 
 * @param tools Pointer to the tools structure.
 * @param parser Pointer to the parsed exit command.
 * @return The exit status.
 */
int	cmd_exit(t_tools *tools, t_parser *parser)
{
	if (parser->str[1])
	{
		if (parser->str[1])
		{
			if (check_exit_args(parser) == 0)
			{
				global_status()->nbr = 2;
				tools->exit = 255;
				exit_err(2, parser->str[1]);
				return (global_status()->nbr);
			}
			else
				global_status()->nbr = ft_atoi(parser->str[1]);
		}
		if (parser->str[2] != NULL)
		{
			global_status()->nbr = EXIT_FAILURE;
			exit_err(1, parser->str[0]);
			return (global_status()->nbr);
		}
	}
	tools->exit = 1;
	if (!parser->next)
		ft_putstr_fd("exit\n", STDIN_FILENO);
	return (global_status()->nbr);
}
