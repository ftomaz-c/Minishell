#include "../../includes/builtins.h"
/**
 * @brief Prints the arguments following the echo 
 * command without a newline character.
 * 
 * This function prints the arguments following the echo 
 * command without appending a newline character.
 * 
 * @param command Pointer to the parser struct containing command information.
 * @param pos     Index of the first argument to print.
 * 
 * @note This function assumes the validity of the command struct.
 * 
 * @warning Behavior is undefined if command is NULL 
 * or if the specified index is out of bounds.
 * 
 * @see printf
 * 
 * @example
 * ```
 * // Example usage of echo_n_print function
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * echo_n_print(command, 1); // Print arguments without a newline character
 * ```
 */

void	echo_n_print(t_parser *command, int pos)
{
	int		j;

	pos++;
	while (command->str[pos])
	{
		j = 0;
		while (command->str[pos][j])
		{
			printf("%c", command->str[pos][j]);
			j++;
		}
		if (command->str[pos + 1])
			printf(" ");
		pos++;
	}
}
/**
 * @brief Prints the arguments following the echo
 *  command with a newline character.
 * 
 * This function prints the arguments following the echo 
 * command with a newline character appended after each argument.
 * 
 * @param command Pointer to the parser struct containing command information.
 * @param pos     Index of the first argument to print.
 * 
 * @note This function assumes the validity of the command struct.
 * 
 * @warning Behavior is undefined if command is NULL or 
 * if the specified index is out of bounds.
 * 
 * @see printf
 * 
 * @example
 * ```
 * // Example usage of echo_print function
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * echo_print(command, 1); // Print arguments with a newline character
 * ```
 */

void	echo_print(t_parser *command, int pos)
{
	int		j;

	while (command->str[pos])
	{
		j = 0;
		while (command->str[pos][j])
		{
			printf("%c", command->str[pos][j]);
			j++;
		}
		if (command->str[pos][pos + 1])
			printf(" ");
		pos++;
	}
	printf("\n");
}
/**
 * @brief Executes the echo command, printing its arguments 
 * with or without a newline character.
 * 
 * This function executes the echo command, which prints its
 *  arguments to the standard output.
 * It supports printing arguments with or without a newline
 *  character based on the presence of the "-n" option.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the echo command.
 * 
 * @note This function assumes the validity of the command struct.
 * 
 * @warning Behavior is undefined if command is NULL.
 * 
 * @see printf, ft_strcmp, global_status
 * 
 * @example
 * ```
 * // Example usage of echo function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = echo(tools, command); // Execute the echo command
 * // status will be the global status after executing the echo command.
 * ```
 */

int	echo(t_tools *tools, t_parser *command)
{
	int	i;

	i = 1;
	(void)tools;
	if (!command->str[i])
		printf("\n");
	else if (ft_strcmp(command->str[i], "-n") == 0)
		echo_n_print(command, i);
	else
		echo_print(command, i);
	g_status = EXIT_SUCCESS;
	return (g_status);
}
