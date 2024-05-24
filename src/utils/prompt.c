/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 17:54:22 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_strncmp(home_var, str[4], home_var_len) == 0)
	{
		tmp = ft_substr(str[4], home_var_len, ft_strlen(str[4]) - home_var_len);
		free(str[4]);
		str[4] = ft_strjoin("~", tmp);
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
 */
char	**generate_prompt(t_tools *tools)
{
	char	**str;

	str = ft_calloc(10, sizeof (char *));
	if (!str)
		return (NULL);
	str[0] = ft_strdup(tools->user);
	str[1] = ft_strdup("@");
	str[2] = ft_strdup(tools->name);
	str[3] = ft_strdup(":");
	str[4] = ft_strdup(tools->pwd);
	str[5] = ft_strdup("$ ");
	if (ft_strlen(str[1]) == 0)
	{
		free(str[0]);
		str[0] = ft_strdup("guest");
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
 */
void	prompt_line(t_tools *tools)
{
	char	*prompt;
	char	**str;
	char	*tmp;
	int		i;

	str = generate_prompt(tools);
	if (!str)
		return ;
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
	tools->prompt = ft_strdup(prompt);
	free(prompt);
}
