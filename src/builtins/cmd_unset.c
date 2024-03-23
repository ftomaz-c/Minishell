#include "../../includes/builtins.h"

/**
 * @brief Checks if a variable exists in the environment 
 * and allocates memory for its name.
 * 
 * This function checks if a variable exists in the
 *  environment based on its name.
 * It allocates memory for the variable name and copies 
 * the name until the first '=' character.
 * 
 * @param tools Pointer to the tools struct containing 
 * environment information.
 * @param str   Pointer to the string containing the variable declaration.
 * 
 * @return 1 if the variable already exists, 0 otherwise.
 * 
 * @note This function assumes the validity of the 
 * tools struct and input string.
 *       It allocates memory for the variable name, 
 * which should be freed by the caller.
 * 
 * @warning Behavior is undefined if tools or str is NULL.
 * 
 * @see ft_calloc, copy_var_name, check_var_path
 * 
 * @example
 * ```
 * // Example usage of check_var function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * char *str = "PATH=/bin:/usr/bin"; // Sample variable declaration
 * int exists = check_var(tools, str); // Check if 
 * the variable exists in the environment
 * // exists will be 0 if the variable doesn't exist, otherwise 1.
 * ```
 */

int	check_var(t_tools *tools, char *str)
{
	char	*var_path;
	int		equal_pos;
	int		i;

	i = 0;
	equal_pos = find_char_position(str, '=');
	while (str[i] && i < equal_pos)
		i++;
	var_path = ft_calloc(sizeof(char *), i + 1);
	if (!var_path)
		return (1);
	copy_var_name(var_path, str, i);
	if (check_var_path(tools->env, var_path))
	{
		free(var_path);
		return (1);
	}
	free(var_path);
	return (0);
}

/**
 * @brief Removes a variable from the environment.
 * 
 * This function removes a variable from the environment based on its name.
 * It creates a new environment array without the specified variable.
 * 
 * @param tools Pointer to the tools struct containing environment information.
 * @param str   Pointer to the string containing the variable name.
 * @param i     Index of the variable to remove from the environment.
 * 
 * @note This function assumes the validity of 
 * the tools struct and input string.
 *       It reallocates memory for the environment
 *  array, which should be freed by the caller.
 * 
 * @warning Behavior is undefined if tools or str is NULL.
 * 
 * @see ft_calloc, count_lines, find_char_position, ft_strncmp, free_list
 * 
 * @example
 * ```
 * // Example usage of unset_var_from_env function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * char *str = "PATH"; // Variable name to unset
 * int i = find_var_index(tools->env, str); 
 * // Find index of the variable in the environment
 * unset_var_from_env(tools, str, i); 
 * // Remove the variable from the environment
 * ```
 */

void	unset_var_from_env(t_tools *tools, char *str, int i)
{
	int		j;
	char	**new_env;
	int		equal_pos;

	new_env = ft_calloc(count_lines(tools->env) + 1, sizeof(char *));
	if (!new_env)
		return ;
	j = 0;
	while (tools->env[i])
	{
		equal_pos = find_char_position(tools->env[i], '=');
		if (ft_strncmp(str, tools->env[i], equal_pos) != 0)
		{
			new_env[j] = ft_strdup(tools->env[i]);
			if (!new_env[j])
			{
				free_list(new_env);
				return ;
			}
			j++;
		}
		i++;
	}
	free_list(tools->env);
	tools->env = new_env;
}

/**
 * @brief Unsets specified variables from the environment.
 * 
 * This function unsets specified variables from 
 * the environment by removing them from the environment array.
 * 
 * @param tools   Pointer to the tools struct containing environment information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return EXIT_SUCCESS if variables are successfully unset.
 * 
 * @note This function assumes the validity of the tools and command structs.
 * 
 * @warning Behavior is undefined if tools or command is NULL.
 * 
 * @see check_var, unset_var_from_env, global_status, printf
 * 
 * @example
 * ```
 * // Example usage of unset function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = unset(tools, command); 
 * // Unset specified variables from the environment
 * // status will be EXIT_SUCCESS if variables are successfully unset.
 * ```
 */

int	cmd_unset(t_tools *tools, t_parser *command)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	if (!command->str[i])
		printf("\n");
	while (command->str[i])
	{
		if (check_var(tools, command->str[i]))
			unset_var_from_env(tools, command->str[i], pos);
		i++;
	}
	g_status = EXIT_SUCCESS;
	return (g_status);
}
