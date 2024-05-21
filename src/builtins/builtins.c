/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 20:20:19 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/**
 * @brief Determines if a command is a built-in function and 
 * returns its function pointer.
 * 
 * This function determines if a command is a built-in 
 * function by comparing it with
 * predefined built-in command names. If a match is found, 
 * it returns the function pointer
 * corresponding to that built-in command. Otherwise, it returns NULL.
 * 
 * @param str The command string to check.
 * 
 * @return Returns a function pointer to the built-in function if 
 * the command is built-in, otherwise NULL.
 */
int	(*is_builtin(char *str))(t_tools *tools, t_parser *parser)
{
	size_t		i;
	t_builtin	builtin_array[8];

	builtin_array[0] = (t_builtin){"echo", cmd_echo};
	builtin_array[1] = (t_builtin){"cd", cmd_cd};
	builtin_array[2] = (t_builtin){"pwd", cmd_pwd};
	builtin_array[3] = (t_builtin){"export", cmd_export};
	builtin_array[4] = (t_builtin){"unset", cmd_unset};
	builtin_array[5] = (t_builtin){"env", cmd_env};
	builtin_array[6] = (t_builtin){"exit", cmd_exit};
	builtin_array[7] = (t_builtin){"history", cmd_history};
	i = 0;
	while (i < (sizeof(builtin_array) / sizeof(builtin_array[0])))
	{
		if (ft_strcmp(builtin_array[i].name, str) == 0)
			return (builtin_array[i].builtin);
		i++;
	}
	return (NULL);
}
