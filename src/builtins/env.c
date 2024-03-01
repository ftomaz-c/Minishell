#include "../../includes/builtins.h"

/**
 * @brief Prints the environment variables.
 * 
 * This function prints the environment variables to the standard output.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the env command.
 * 
 * @note This function assumes the validity of the tools struct.
 * 
 * @warning Behavior is undefined if tools is NULL.
 * 
 * @see printf, global_status
 * 
 * @example
 * ```
 * // Example usage of env function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = env(tools, command); // Execute the env command
 * // status will be the global status after executing the env command.
 * ```
 */

int	env(t_tools *tools, t_parser *command)
{
	int	i;

	i = 0;
	(void)tools;
	(void)command;
	while (tools->env[i])
	{
		if (!ft_strchr(tools->env[i], '='))
			i++;
		else
		{
			if (!tools->env[i])
				break ;
			printf("%s\n", tools->env[i]);
			i++;
		}
	}
	g_status = EXIT_SUCCESS;
	return (g_status);
}
