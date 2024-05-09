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

int	cmd_env(t_tools *tools, t_parser *command)
{
	int		i;
	t_tools	*tmp;

	i = 0;
	(void)tools;
	if (command->str[1])
	{
		printf("env: '%s': no such file or directory\n", command->str[1]);
		g_status = 127;
		return (g_status);
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
			printf("%s\n", tmp->env[i]);
			i++;
		}
	}
	g_status = EXIT_SUCCESS;
	return (g_status);
}
