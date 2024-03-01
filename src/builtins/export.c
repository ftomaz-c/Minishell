#include "../../includes/builtins.h"

/**
 * @brief Sort and print environment variables.
 * 
 * This function sorts the environment variables alphabetically 
 * and prints them.
 * 
 * @param tools Pointer to tools structure containing environment variables.
 * 
 * @note This function assumes that the necessary helper
 * functions like get_env_export(), sort_array(), 
 * ft_strncmp(), and free_list() are defined elsewhere.
 * 
 * @see get_env_export(), sort_array(), ft_strncmp(), free_list()
 * 
 * @example
 */

void	sort_print_env(t_tools *tools)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = get_env_export(tools->env, i);
	sort_array(env_copy);
	while (env_copy[i])
	{	
		if (ft_strncmp(env_copy[i], "declare -x _=", 13) == 0)
			i++;
		else
			printf("%s\n", env_copy[i++]);
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
 * 
 * @note This function assumes that the necessary helper functions 
 * like ft_strcmp(), find_char_position(),
 * and ft_isalpha_plus_underscore() are defined elsewhere.
 * 
 * @see ft_strcmp(), find_char_position(), ft_isalpha_plus_underscore()
 * 
 * @warning This function prints error messages to stdout if 
 * the identifier is not valid.
 * 
 * @example
 * 
 */

void	export_err(int err, char *str)
{
	if (err == 1)
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	global_status = err;
}

int	check_valid_export(char *parser)
{
	int	i;
	int	equal_pos;

	i = 0;
	if (ft_strcmp(parser, "=") == 0 || parser[i] == '='
		|| !ft_isalpha_plus_underscore(parser[i]))
	{	
		export_err(1, parser);
		return (0);
	}
	i = 1;
	equal_pos = find_char_position(parser, '=');
	while (parser[i] && i < equal_pos)
	{
		if (parser[i] != '_'  && !ft_isalnum(parser[i]) && parser[i] != '+')
		{
			export_err(1, parser);
			return (0);
		}
		i++;
	}
	return (1);
}
/**
 * @brief Export a variable to the environment.
 * 
 * This function adds a new environment variable specified in the 
 * input string to the environment.
 * 
 * @param tools Pointer to tools structure containing environment variables.
 * @param str String containing the variable to export.
 * 
 * @note This function assumes that the necessary helper 
 * functions like get_new_var(), 
 * ft_calloc(), copy_var_to_env(), and free_list() are defined elsewhere.
 * 
 * @see get_new_var(), ft_calloc(), copy_var_to_env(), free_list()
 * 
 * @warning This function modifies the environment by adding a new variable. 
 * It relies on memory allocation and deallocation, so care 
 * should be taken to avoid memory leaks.
 * 
 * @example
 * 
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
 * 
 * @note This function assumes that the necessary helper functions 
 * like find_char_position(),
 * ft_calloc(), copy_var_name(), check_var_path(), and 
 * substitute_env_var_value() are defined elsewhere.
 * 
 * @see find_char_position(), ft_calloc(), copy_var_name(), check_var_path(),
 * substitute_env_var_value()
 * 
 * @warning This function modifies the input string by 
 * substituting the variable value. 
 * It also relies on memory allocation and deallocation, so care should be 
 * taken to avoid memory leaks.
 * 
 * @example
 * 
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
 * 
 * @note This function assumes that the tools and parser 
 * structures are initialized 
 * and valid. It also assumes that the necessary functions
 *  like sort_print_env(), 
 * check_valid_export(), check_if_var_exists(), and 
 * export_variable_to_env() are defined elsewhere.
 * 
 * @warning This function modifies the environment by exporting variables. 
 * Care should be taken when using it in multithreaded or critical sections.
 * 
 * @see sort_print_env(), check_valid_export(), check_if_var_exists(), 
 * export_variable_to_env()
 * 
 * @example
 * 
 * ```
 * // Export a variable
 * export(&tools, &parser);
 * 
 * // Export multiple variables
 * export(&tools, &parser);
 * ```
 */

int	export(t_tools *tools, t_parser *command)
{
	int	i;

	i = 1;
	g_status = EXIT_SUCCESS;
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
	return (g_status);
}
