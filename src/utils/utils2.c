/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:09:48 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/**
 * @brief Calculates the length of a string until newline character.
 * 
 * This function calculates the length of a string until it encounters
 * either a null terminator or a newline character.
 * 
 * @param s Pointer to the string.
 * 
 * @return Returns the length of the string until the newline character 
 * or null terminator.
 */
size_t	ft_strlen_nl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	return (i);
}

/**
 * @brief Constructs a file path by appending a file name 
 * to the user's home directory path.
 * 
 * This function constructs a file path by concatenating
 *  the user's home directory path
 * obtained from the HOME environment variable with
 *  the provided file name.
 * 
 * @param file_name The name of the file to append to
 * the home directory path.
 * 
 * @return A dynamically allocated string containing the 
 * constructed file path.
 *         The caller is responsible for freeing the memory 
 * allocated for the string.
 *         Returns NULL if memory allocation fails or if the
 *  HOME environment variable is not set.
 */
char	*get_file_path_from_home(char *home, char *file_name)
{
	char	*home_var;
	char	*tmp;

	home_var = ft_strjoin(home, "/");
	if (!home_var)
		return (NULL);
	tmp = ft_strjoin(home_var, file_name);
	if (!tmp)
		return (NULL);
	free(home_var);
	return (tmp);
}

/**
 * @brief Retrieves the value of a variable from the environment.
 * 
 * This function searches the environment variables
 * for a specific variable
 * and returns its value.
 * 
 * @param envp The array of environment variables.
 * @param var The name of the variable to retrieve.
 * 
 * @return A pointer to the value of the variable if found,
 * or NULL if not found or on error.
 */
char	*get_var_from_env(char **env, char *var)
{
	int		index;
	char	*value;

	index = 0;
	if (!env || !var)
		return (NULL);
	while (env[index])
	{
		if (compare_var_to_env(env[index], var))
			break ;
		index++;
	}
	if (env[index])
		value = ft_substr(env[index], ft_strlen(var) + 1,
				ft_strlen(env[index]));
	else
		value = NULL;
	return (value);
}

/**
 * @brief Copies the environment variables into a new array.
 * 
 * This function creates a copy of the environment variables
 * and stores them
 * in a new dynamically allocated array.
 * 
 * @param envp The array of environment variables.
 * 
 * @return A pointer to the new array of environment variables,
 * or NULL on error.
 */
char	**get_env(char **envp)
{
	char	**env;
	int		count;
	int		index;

	count = 0;
	if (!envp)
		return (NULL);
	while (envp[count])
		count++;
	env = ft_calloc(sizeof(char *), count + 1);
	if (env == NULL)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		env[index] = ft_strdup(envp[index]);
		if (env[index] == NULL)
			return (NULL);
		index++;
	}
	return (env);
}

/**
 * @brief Frees the memory allocated for a null-terminated array of strings.
 * 
 * This function frees the memory allocated for each string in the array 'list',
 * as well as the memory allocated for the array itself.
 * 
 * @param list Pointer to the array of strings to free.
 */
void	free_list(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
