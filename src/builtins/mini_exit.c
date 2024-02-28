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

int	check_exit_args(t_parser *parser)
{
	int	j;

	j = 0;
	while (parser->str[1][j])
	{
		if (!ft_isdigit(parser->str[1][j]))
			return (0);
		j++;
	}
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

int	mini_exit(t_tools *tools, t_parser *parser)
{
	if (parser->str[1])
	{
		if (!check_exit_args(parser))
		{
			g_status = 2;
			tools->exit = 255;
			printf("exit\nbash: exit: %s: numeric argument required\n",
				parser->str[1]);
			return (g_status);
		}
	}
	if (parser->str[2] != NULL)
	{
		printf("exit\nbash: exit: too many arguments\n");
		g_status = EXIT_FAILURE;
		return (g_status);
	}
	else
		tools->exit = ft_atoi(parser->str[1]);
	printf("exit\n");
	tools->exit = 1;
	g_status = EXIT_SUCCESS;
	return (g_status);
}
