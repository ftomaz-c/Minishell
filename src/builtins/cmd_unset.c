/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 20:26:43 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
