#include "../../includes/expander.h"

/**
 * @brief Adds quotes around a string.
 * 
 * This function adds quotes around a given string, with
 *  the option to choose single or double quotes.
 * If the string is already enclosed in quotes, it leaves it unchanged.
 * 
 * @param j Starting index for the value array.
 * @param str The input string.
 * @param quote The desired quote character (' or ").
 * @param value The array to store the modified string.
 * 
 * @return The modified string with added quotes.
 * 
 * @note The input string (str) is assumed to be valid and null-terminated.
 * 
 * @warning The value array must have enough memory allocated
 *  to accommodate the modified string.
 * 
 * @see None.
 * 
 * @example
 * ```
 * char *result = add_quotes(0, "example", '"', malloc(9));
 * // result now contains "example"
 * free(result);
 * ```
 */
char	*add_quotes(int j, char *str, char quote, char *value)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!value[0])
		{
			if (quote == '\'')
				quote = '\"';
			else
				quote = '\'';
			value[0] = quote;
		}
		value[j] = str[i];
		i++;
		j++;
		if (str[i] == '\0')
			break ;
	}
	value[j] = quote;
	free(str);
	return (value);
}

/**
 * @brief Adds quotes to a string value if it's not already quoted.
 * 
 * This function adds quotes around a string value if it's 
 * not already enclosed in quotes.
 * It checks the first occurrence of single or double quotes in 
 * the string to determine the quote character to use.
 * 
 * @param str The input string.
 * @param flagquote Flag indicating whether to trim spaces from the input string.
 * @param j Starting index for the value array.
 * @param i Starting index for iterating through the input string.
 * 
 * @return The modified string with added quotes (if necessary).
 * 
 * @note The input string (str) is assumed to be valid and null-terminated.
 * 
 * @warning Memory is allocated within the function and needs 
 * to be freed by the caller to avoid memory leaks.
 * 
 * @see ft_strtrim
 * 
 * @example
 * ```
 * char *result = add_quotes_to_value("example", 1, 0, 0);
 * // result now contains "example"
 * free(result);
 * ```
 */

char	get_quote_flag(char *str, int i)
{
	char	quote;

	quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			break ;
		}
		i++;
	}
	return (quote);
}

char	*add_quotes_to_value(char *str, int flagquote, int j, int i)
{
	char	*value;
	char	*tmp;
	char	quote;

	quote = '\0';
	if (str == NULL)
		return (NULL);
	if (flagquote == 2)
		quote = '\'';
	else
		quote = get_quote_flag(str, i);
	if (quote == '\0')
		return (str);
	value = ft_calloc(sizeof(char *), ft_strlen(str) + 2);
	if (!value)
		return (NULL);
	if (flagquote)
	{
		tmp = ft_strtrim(str, " ");
		free(str);
		str = tmp;
	}
	value = add_quotes(j, str, quote, value);
	return (value);
}

/**
 * @brief Builds a string by concatenating prefix, value, and suffix.
 * 
 * This function builds a string by concatenating 
 * a prefix, a value, and a suffix.
 * If the value is NULL, it's replaced with an empty string.
 * 
 * @param value The value to be concatenated.
 * @param prefix The prefix string.
 * @param suffix The suffix string.
 * 
 * @return The concatenated string.
 * 
 * @note Memory is allocated within the function and needs 
 * to be freed by the caller to avoid memory leaks.
 * 
 * @warning The input strings (value, prefix, suffix) are 
 * assumed to be valid and null-terminated.
 * 
 * @see ft_strjoin
 * 
 * @example
 * ```
 * char *result = build_str("example", "Prefix ", " Suffix");
 * // result now contains "Prefix example Suffix"
 * free(result);
 * ```
 */
char	*build_str(char *value, char *prefix, char *suffix)
{
	char	*str;
	char	*tmp;

	if (value == NULL)
		tmp = ft_strjoin(prefix, "");
	else
		tmp = ft_strjoin(prefix, value);
	str = ft_strjoin(tmp, suffix);
	free(value);
	free(tmp);
	free(suffix);
	free(prefix);
	return (str);
}
