#include "../../includes/builtins.h"
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
 * 
 * @note This function assumes the validity of the parser struct.
 * 
 * @warning Behavior is undefined if parser is NULL or 
 * if the argument is not present in parser->str[1].
 * 
 * @see ft_isdigit
 * 
 * @example
 * ```
 * // Example usage of check_exit_args function
 * t_parser *parser = initialize_parser(); // Initialize parser struct
 * int valid = check_exit_args(parser); // Check if the
 *  argument to the exit command is a valid integer
 * // valid will be 1 if the argument is a valid integer, otherwise 0.
 * ```
 */

long long	check_if_within_range(char *status)
{
	long long	nbr;

	nbr = ft_atoll(status);
	if (errno == ERANGE)
		nbr = 0;
	return (nbr);
}

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
	if (!parser->str[1][j])
		return (0);
	while (ft_isdigit(parser->str[1][j]))
		j++;
	if (parser->str[1][j - 1] == '0')
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
 * 
 * @note This function assumes the validity of the tools and parser structs.
 * 
 * @warning Behavior is undefined if tools or parser is NULL.
 * 
 * @see check_exit_args, global_status, printf, ft_atoi
 * 
 * @example
 * ```
 * // Example usage of mini_exit function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *parser = initialize_parser(); // Initialize parser struct
 * int status = mini_exit(tools, parser); // Execute the exit command
 * // status will be the global status after executing the exit command.
 * ```
 */

void	exit_err(int err, char *str)
{
	if (err == 1)
	{
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	}
	else if (err == 2)
	{
		ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
}

int	mini_exit(t_tools *tools, t_parser *parser)
{
	if (parser->str[1])
	{
		if (parser->str[1])
		{
			if (!check_exit_args(parser))
			{
				g_status = 2;
				tools->exit = 255;
				exit_err(2, parser->str[1]);
				return(g_status);
			}
			else
				g_status = ft_atoi(parser->str[1]);
		}
		if (parser->str[2] != NULL)
		{
			g_status = EXIT_FAILURE;
			exit_err(1, parser->str[0]);
			return (g_status);
		}
	}
	tools->exit = 1;
	return (g_status);
}
