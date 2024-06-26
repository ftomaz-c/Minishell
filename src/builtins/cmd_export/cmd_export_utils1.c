/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 18:55:53 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

/**
 * @brief Copy variable value surrounded by quotes.
 * 
 * This function copies the variable value from the 
 * input string starting from the specified position
 * and surrounds it with double quotes.
 * 
 * @param var_path Pointer to the destination string 
 * where the value will be copied.
 * @param str Input string containing the variable and its value.
 * @param start Starting position from where to copy the value.
 */
void	copy_var_value_quotes(char *var_path, char *str, int start)
{
	int	i;

	i = 1;
	if (start >= (int)ft_strlen(str))
	{
		var_path = NULL;
		return ;
	}
	while (start < (int)ft_strlen(str))
	{
		if (!var_path[0])
			var_path[0] = '\"';
		if (start >= (int)ft_strlen(str))
			break ;
		var_path[i] = str[start];
		i++;
		start++;
	}
	var_path[i] = '\"';
	var_path[++i] = '\0';
}

/**
 * @brief Copy variable name.
 * 
 * This function copies the variable name from the 
 * input string up to the specified position.
 * 
 * @param var_path Pointer to the destination string 
 * where the name will be copied.
 * @param str Input string containing the variable and its value.
 * @param equal_pos Position of the equal sign '=' 
 * separating the variable name and value.
 */
int	copy_var_name(char *var_path, char *str, int equal_pos)
{
	int	i;
	int	j;
	int	plus_flag;

	i = 0;
	j = 0;
	plus_flag = 0;
	while (str[i] && i <= equal_pos)
	{
		if (str[i] == '+')
		{
			plus_flag = 1;
			i++;
		}
		var_path[j++] = str[i++];
	}
	return (plus_flag);
}

/**
 * @brief Prepare a variable for exporting.
 * 
 * This function prepares a variable for exporting
 *  by combining its name and value.
 * 
 * @param str Input string containing the variable and its value.
 * 
 * @return Returns a newly allocated string containing the prepared variable, 
 * or NULL if memory allocation fails.
 */
char	*prepare_var(char *str)
{
	char	*var_path;
	char	*var_value;
	char	*new_path;
	int		equal_pos;

	equal_pos = find_char_position(str, '=');
	var_path = ft_calloc(sizeof(char *), equal_pos + 1);
	if (!var_path)
		return (NULL);
	copy_var_name(var_path, str, equal_pos);
	var_value = ft_calloc(sizeof(char *),
			(ft_strlen(str) - (equal_pos + 1)) + 3);
	if (!var_value)
		return (NULL);
	if (!str[equal_pos + 1])
		ft_strcpy(var_value, "\"\"");
	else
		copy_var_value_quotes(var_value, str, equal_pos + 1);
	new_path = ft_strjoin(var_path, var_value);
	free(var_path);
	free(var_value);
	return (new_path);
}

/**
 * @brief Get environment variables for export.
 * 
 * This function prepares environment variables for export by 
 * adding "declare -x " prefix to each variable.
 * 
 * @param envp Pointer to the array of environment variables.
 * @param i Index to start scanning the environment variables from.
 * 
 * @return Returns a newly allocated array of strings containing
 *  the prepared environment variables, or NULL if memory allocation fails.
 */
void	get_env_export(char **envp, int i, char *tmp, char ***env)
{
	while (envp[i])
		i++;
	*env = ft_calloc(sizeof(char **), i + 1);
	if (*env == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			tmp = prepare_var(envp[i]);
			(*env)[i] = ft_strjoin("declare -x ", tmp);
			free(tmp);
			if ((*env)[i] == NULL)
			{
				free_list(*env);
				return ;
			}
		}
		else
			(*env)[i] = ft_strjoin("declare -x ", envp[i]);
		i++;
	}
	return ;
}

int	validate_export_name(char *str, int equal_pos, int i)
{
	while (str[i] && i < equal_pos)
	{
		if (str[i] != '_' && !ft_isalnum(str[i]) && str[i] != '+')
		{
			export_err(1, str);
			return (0);
		}
		if (str[i] == '+' && str[i + 1] != '=')
		{
			export_err(1, str);
			return (0);
		}
		i++;
	}
	return (1);
}
