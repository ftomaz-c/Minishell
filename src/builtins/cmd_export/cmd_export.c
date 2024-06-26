/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 18:56:12 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

/**
 * @brief Sort and print environment variables.
 * 
 * This function sorts the environment variables alphabetically 
 * and prints them.
 * 
 * @param tools Pointer to tools structure containing environment variables.
 */
void	sort_print_env(t_tools *tools)
{
	char	**env_copy;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	env_copy = NULL;
	get_env_export(tools->env, i, tmp, &env_copy);
	sort_array(env_copy);
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], "declare -x _=", 13) == 0)
			i++;
		else
		{
			ft_putstr_fd(env_copy[i++], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	free_list(env_copy);
}

/**
 * @brief Check if a string is a valid export identifier.
 * 
 * This function checks if the input string is a valid identifier 
 * for exporting as an environment variable.
 * 
 * @param parser String to check for validity as an export identifier.
 * 
 * @return Returns 1 if the string is a valid export identifier, 0 otherwise.
 */
int	check_valid_export(char *str)
{
	int	i;
	int	equal_pos;

	i = 0;
	if (ft_strcmp(str, "=") == 0 || str[i] == '='
		|| (!ft_isalpha(str[i]) && str[i] != '_'))
	{
		export_err(1, str);
		return (0);
	}
	equal_pos = find_char_position(str, '=');
	if (equal_pos == (int)ft_strlen(str) && ft_strchr(str, '+'))
	{
		export_err(1, str);
		return (0);
	}
	return (validate_export_name(str, equal_pos, 1));
}

/**
 * @brief Export a variable to the environment.
 * 
 * This function adds a new environment variable specified in the 
 * input string to the environment.
 * 
 * @param tools Pointer to tools structure containing environment variables.
 * @param str String containing the variable to export.
 */
void	export_variable_to_env(t_tools *tools, char *str)
{
	int		i;
	char	*var_value;
	char	**new_array;

	i = 0;
	var_value = NULL;
	get_new_var(&var_value, str);
	while (tools->env[i])
		i++;
	new_array = ft_calloc(sizeof(char *), i + 2);
	if (new_array == NULL)
		return ;
	if (!copy_var_to_env(tools, new_array, var_value, i))
		return ;
	free(var_value);
	free_list(tools->env);
	tools->env = new_array;
}

/**
 * @brief Check if a variable exists in the environment.
 * 
 * This function checks if the variable specified in the 
 * string exists in the environment.
 * If the variable exists, it substitutes its value in the input string.
 * 
 * @param tools Pointer to tools structure containing environment variables.
 * @param str String containing the variable to check.
 * 
 * @return Returns 1 if the variable exists, 0 otherwise.
 */
int	check_if_var_exists(t_tools *tools, char *str)
{
	char	*var_path;
	int		equal_pos;
	int		plus_flag;
	int		i;

	i = 0;
	equal_pos = find_char_position(str, '=');
	while (str[i] && i < equal_pos)
		i++;
	var_path = ft_calloc(sizeof(char *), i + 1);
	if (!var_path)
		return (1);
	plus_flag = copy_var_name(var_path, str, i);
	if (check_var_path(tools->env, var_path))
	{
		if (plus_flag)
			add_value_to_var(tools, var_path, str);
		else
			substitute_env_var_value(tools, var_path, str);
		return (1);
	}
	free(var_path);
	return (0);
}

/**
 * @brief Export environment variables.
 * 
 * This function exports environment variables specified in 
 * the command's arguments 
 * to the environment. If no arguments are provided, it
 *  prints the current environment.
 * 
 * @param tools Pointer to tools structure.
 * @param parser Pointer to parser structure containing 
 * command-line arguments.
 * 
 * @return Returns 0 on success.
 */
int	cmd_export(t_tools *tools, t_parser *command)
{
	int	i;

	i = 1;
	global_status()->nbr = EXIT_SUCCESS;
	if (!command->str[1])
		sort_print_env(tools);
	else
	{
		while (command->str[i])
		{
			if (check_valid_export(command->str[i]))
			{
				if (check_if_var_exists(tools, command->str[i]))
					i++;
				else
				{
					export_variable_to_env(tools, command->str[i]);
					i++;
				}
			}
			else
				i++;
		}
	}
	return (global_status()->nbr);
}
