#include "../../includes/utils.h"

/**
 * @brief Handles abbreviation of the HOME directory 
 * in a string array.
 * 
 * This function replaces the HOME directory path with
 *  a tilde (~) in a string array.
 * It checks if the provided string contains the HOME 
 * directory path at a specific index.
 * If found, it replaces the HOME directory path with a tilde.
 * 
 * @param tools Pointer to the tools struct.
 * @param str   String array to process.
 * 
 * @return Updated string array with HOME directory abbreviation.
 *         If HOME directory is not found or tools struct is 
 * not valid, returns the input string array.
 * 
 * @note This function assumes the existence of the HOME 
 * environment variable.
 *       It assumes the input string array has at least 7 
 * elements, and the HOME directory path is at index 6.
 *       Memory allocated for the updated string array 
 * should be freed by the caller.
 * 
 * @warning Behavior is undefined if tools or str is NULL.
 * 
 * @see get_var_from_env, ft_strlen, ft_strncmp, ft_substr, ft_strjoin
 * 
 * @example
 * ```
 * // Example usage of handle_home_abreviation function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * char **str = {"", "", "", "", "", "", "/home/user/example"};
 *  // Sample input string array
 * char **updated_str = handle_home_abreviation(tools, str); 
 * // Abbreviate HOME directory
 * // After function call, updated_str will contain
 *  {"", "", "", "", "", "", "~/example"}
 * // Remember to free the memory allocated for updated_str 
 * when it's no longer needed.
 * ```
 */

char	**handle_home_abreviation(t_tools *tools, char **str)
{
	char	*home_var;
	int		home_var_len;
	char	*tmp;

	home_var = get_var_from_env(tools->env, "HOME");
	if (!home_var)
		return (str);
	home_var_len = ft_strlen(home_var);
	if (ft_strncmp(home_var, str[6], home_var_len) == 0)
	{
		tmp = ft_substr(str[6], home_var_len, ft_strlen(str[6]) - home_var_len);
		free(str[6]);
		str[6] = ft_strjoin("~", tmp);
		free(tmp);
	}
	free(home_var);
	return (str);
}

/**
 * @brief Generates a customized prompt string based on the 
 * provided tools struct.
 * 
 * This function constructs a prompt string with user, hostname,
 *  current directory, and a trailing "$ ".
 * It retrieves user and current directory information
 * from the provided tools struct.
 * 
 * @param tools Pointer to the tools struct containing user
 *  and current directory information.
 * 
 * @return A string array containing the generated prompt components.
 *         If memory allocation fails, returns NULL.
 * 
 * @note This function assumes the validity of the tools struct.
 *       Memory allocated for the generated string array
 *  should be freed by the caller.
 * 
 * @warning Behavior is undefined if tools is NULL.
 * 
 * @see ft_strdup, handle_home_abreviation
 * 
 * @example
 * ```
 * // Example usage of generate_prompt function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * char **prompt = generate_prompt(tools); // Generate 
 * customized prompt
 * // After function call, prompt will contain {"\033[1;32m", 
 * "username", "@", "hostname", "\033[0m:", "\033[1;34m", 
 * "/current/directory", "\033[0m", "$ "}
 * // Remember to free the memory allocated for prompt when
 *  it's no longer needed.
 * ```
 */

char	**generate_prompt(t_tools *tools)
{
	char	**str;

	str = calloc(10, sizeof (char *));
	if (!str)
		return (NULL);
	str[0] = ft_strdup("\033[1;32m");
	str[1] = ft_strdup(tools->user);
	str[2] = ft_strdup("@");
	str[3] = ft_strdup(tools->name);
	str[4] = ft_strdup("\033[0m:");
	str[5] = ft_strdup("\033[1;34m");
	str[6] = ft_strdup(tools->pwd);
	str[7] = ft_strdup("\033[0m");
	str[8] = ft_strdup("$ ");
	if (ft_strlen(str[1]) == 0)
	{
		free(str[1]);
		str[1] = ft_strdup("guest");
	}
	str = handle_home_abreviation(tools, str);
	return (str);
}

/**
 * @brief Reads a line of input from the user with a customized prompt.
 * 
 * This function displays a customized prompt using the provided tools struct
 * and waits for the user to input a line. It utilizes 
 * the readline library for input.
 * 
 * @param tools Pointer to the tools struct containing prompt information.
 * 
 * @return A dynamically allocated string containing the user input line.
 *         If memory allocation fails or readline fails, returns NULL.
 * 
 * @note This function assumes the validity of the tools struct.
 *       The memory allocated for the input line should 
 * be freed by the caller.
 * 
 * @warning Behavior is undefined if tools is NULL.
 * 
 * @see readline, generate_prompt
 * 
 * @example
 * ```
 * // Example usage of prompt_line function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * char *input = prompt_line(tools); // Prompt user for input
 * // After function call, input will contain the user input line
 * // Remember to free the memory allocated for 
 * input when it's no longer needed.
 * ```
 */

char	*prompt_line(t_tools *tools)
{
	char	*line;
	char	*prompt;
	char	**str;
	char	*tmp;
	int		i;

	str = generate_prompt(tools);
	if (!str)
		return (NULL);
	i = 0;
	prompt = ft_strdup("");
	while (str[i])
	{
		tmp = ft_strjoin(prompt, str[i]);
		free(prompt);
		free(str[i]);
		prompt = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	free(str);
	line = readline(prompt);
	free(prompt);
	return (line);
}
