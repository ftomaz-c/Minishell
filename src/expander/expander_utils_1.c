#include "../../includes/minishell.h"

/**
 * @brief Finds the presence of single quotes in a string.
 * 
 * This function iterates through the given string 
 * `str` to find the presence of single quotes.
 * It returns 1 if at least one single quote is found, otherwise returns 0.
 * 
 * @param str The input string to search for single quotes.
 * 
 * @return Returns 1 if at least one single quote is found, otherwise returns 0.
 * 
 * @note This function only checks for the presence of 
 * single quotes ('), not double quotes (").
 * 
 * @warning This function assumes that the input string is null-terminated.
 * 
 * @see No related functions.
 * 
 * @example
 * 
 * ```
 * // Example usage of find_single_quote function
 * char str1[] = "This is a 'sample' string.";
 * char str2[] = "This string has no single quotes.";
 * 
 * int result1 = find_single_quote(str1); // Returns 1
 * int result2 = find_single_quote(str2); // Returns 0
 * ```
 */

int	find_single_quote(char *str)
{
	int		i;
	char	first_quote;

	first_quote = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			first_quote = str[i];
		if (first_quote == '\'')
			return (1);
		else if (first_quote == '\"')
			break ;
		i++;
	}
	return (0);
}

/**
 * @brief Checks if a character is an alphanumeric 
 * character or an underscore.
 * 
 * This function determines whether a given character is 
 * alphanumeric (either uppercase or lowercase)
 * or an underscore. It is used as a helper function to identify 
 * valid characters in environment variable names.
 * 
 * @param c The character to be checked.
 * 
 * @return Returns 1 if the character is alphanumeric or an
 * underscore, otherwise returns 0.
 * 
 * @note Assumes ASCII character encoding for alphanumeric characters.
 * 
 * @see None
 * 
 * @example
 * ```
 * int result = ft_isalphanum_or_underscore('A');
 * // result will be 1
 * ```
 */

int	ft_isalphanum_or_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= 0 && c <= 9) || c == '_')
		return (1);
	return (0);
}

/**
 * @brief Finds the position of a character within a string.
 * 
 * This function searches for the first occurrence of a specified 
 * character within a given string.
 * 
 * @param str The string to be searched.
 * @param c The character to search for.
 * 
 * @return Returns the position of the character within the string if 
 * found, otherwise returns the length of the string.
 * 
 * @note Assumes the input string is null-terminated.
 * 
 * @see None
 * 
 * @example
 * ```
 * int position = find_char_position_new("example", 'm');
 * // position will be 3
 * ```
 */

int	find_char_position_new(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief Finds the end position of a variable name within a string.
 * 
 * This function determines the end position of a variable 
 * name within a given string.
 * The end position is defined as the position right after
 * the variable name ends, which can include
 * alphanumeric characters and underscores, but not the '=' character.
 * 
 * @param str The string to be analyzed.
 * @param position The starting position of the variable name within the string.
 * 
 * @return Returns the end position of the variable name.
 * 
 * @note Assumes the input string is null-terminated and follows 
 * the variable name syntax.
 * 
 * @see ft_isalphanum_or_underscore
 * 
 * @example
 * ```
 * int end = get_end_position("example_var=123", 7);
 * // end will be 10
 * ```
 */

int	get_end_position(char *str, int position)
{
	int	end;

	if (str[position + 1] == '?')
		end = position + 2;
	else if ((str[position + 1] == '\'' && str[position + 2] == '\\'
			&& str[position + 4] == '\''))
		end = position + 4;
	else
	{
		end = position + 1;
		while (str && str[end] && ft_isalphanum_or_underscore(str[end])
			&& str[end] != '=')
			end++;
	}
	return (end);
}

/**
 * @brief Adds a prefix and suffix to a string based on a variable name.
 * 
 * This function constructs a new string by adding a prefix,
 * the value corresponding to the variable name from
 * the environment, and a suffix to the original string.
 * 
 * @param str The original string.
 * @param env The environment containing variable-value pairs.
 * @param position The position of the '$' character within the original string.
 * @param end The end position of the variable name within the original string.
 * 
 * @return Returns the modified string with the added prefix and suffix.
 * 
 * @note The function dynamically allocates memory for the
 *  new string and must be freed after use.
 * 
 * @see ft_substr, ft_strjoin, get_var_from_env
 * 
 * @example
 * ```
 * char *result = add_prefix_and_suffix("prefix$var_suffix",
 * environment, 6, 9);
 * // result will be "prefixvalue_suffix"
 * ```
 */

char	*add_prefix_and_suffix(char *str, char **env, int position, int end)
{
	char	*prefix;
	char	*var;
	char	*value;
	char	*suffix;

	prefix = ft_substr(str, 0, position);
	var = ft_substr(str, position + 1, end - position - 1);
	if (ft_strncmp(var, "?", 1) == 0)
		value = ft_itoa(g_status);
	else
		value = get_var_from_env(env, var);
	free(var);
	suffix = ft_substr(str, end, ft_strlen(str) - end);
	if (prefix[0] == '\"' && str[1] == '$')
	{	
		free(prefix);
		prefix = ft_strdup("");
		value = add_quotes_to_value(value, 0, 1, 0);
	}
	else
		value = add_quotes_to_value(value, 1, 1, 0);
	str = build_str(value, prefix, suffix);
	return (str);
}
