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
 * 
 * @note This function assumes that 'str' is a valid null-terminated string.
 *       The built-in commands and their function pointers are 
 * stored in a static array.
 *       Each entry in the array consists of the command name and its
 *  corresponding function pointer.
 *       The function pointers have the signature int 
 * (*)(t_tools *, t_parser *), where 't_tools' represents
 *       a structure containing information about the 
 * built-ins and 't_parser' represents a node
 *       in the parser linked list.
 *       This function iterates through the array of built-in
 *  commands to find a match with the input string.
 *       It uses strncmp() to compare the input string with each command name.
 *       If a match is found, it returns the function
 *  pointer associated with that command.
 *       If no match is found, it returns NULL.
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
