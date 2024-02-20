#include "../../includes/builtins.h"

/**
 * @brief Determines if a command is a built-in function and returns its function pointer.
 * 
 * This function determines if a command is a built-in function by comparing it with
 * predefined built-in command names. If a match is found, it returns the function pointer
 * corresponding to that built-in command. Otherwise, it returns NULL.
 * 
 * @param str The command string to check.
 * 
 * @return Returns a function pointer to the built-in function if the command is built-in, otherwise NULL.
 * 
 * @note This function assumes that 'str' is a valid null-terminated string.
 *       The built-in commands and their function pointers are stored in a static array.
 *       Each entry in the array consists of the command name and its corresponding function pointer.
 *       The function pointers have the signature int (*)(t_tools *, t_parser *), where 't_tools' represents
 *       a structure containing information about the built-ins and 't_parser' represents a node
 *       in the parser linked list.
 *       This function iterates through the array of built-in commands to find a match with the input string.
 *       It uses strncmp() to compare the input string with each command name.
 *       If a match is found, it returns the function pointer associated with that command.
 *       If no match is found, it returns NULL.
 */

int	(*is_builtin(char *str))(t_tools *tools, t_parser *parser)
{
	static struct {
		char	*name;
		int		(*builtin)(t_tools *, t_parser *);
    } builtin_array[] = {
        {"echo", echo},
        {"cd", cd},
        {"pwd", pwd},
        {"export", export},
        {"unset", unset},
        {"env", env},
        {"exit", mini_exit}
    };
	size_t		i;

	i = 0;
	while (i < (sizeof(builtin_array) / sizeof(builtin_array[0])))
	{
		if (ft_strncmp(builtin_array[i].name, str, ft_strlen(builtin_array[i].name)) == 0)
			return (builtin_array[i].builtin);
		i++;
	}
	return (NULL);
}
