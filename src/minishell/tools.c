/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/22 20:13:41 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Handles the value of the "SHLVL" environment variable and calculates 
 * the new shell level.
 *
 * This function takes the current value of the "SHLVL" environment variable, 
 * calculates the new shell level, and assigns it to the provided `new_lvl` 
 * pointer. If the current level is not provided, it initializes to 1.
 * If the current level is less than 0, it sets the level to 0. If the new level
 * exceeds 1000, it resets to 1 and prints a warning message.
 *
 * @param pre_lvl A string representing the previous value of "SHLVL". Can be 
 * NULL.
 * @param new_lvl A pointer to a string where the new value of "SHLVL" will be 
 * stored.
 * @param lvl A size_t variable to store the intermediate level value.
 */
void	handle_shlvl(char *pre_lvl, char **new_lvl, size_t lvl)
{
	if (!pre_lvl)
		lvl = 1;
	else
		lvl = ft_atoll(pre_lvl);
	if ((int)lvl < 0)
		*new_lvl = ft_itoa(0);
	else
		*new_lvl = ft_itoa(lvl + 1);
	if (ft_atoll(*new_lvl) > 1000)
	{
		*new_lvl = ft_itoa(1);
		ft_putstr_fd("bash: warning: shell level (", STDERR_FILENO);
		ft_putstr_fd(ft_itoa(lvl + 1), STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to ", STDERR_FILENO);
		ft_putstr_fd(*new_lvl, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/**
 * @brief Updates the "SHLVL" environment variable in the `tools` structure.
 *
 * This function iterates through the environment variables stored in 
 * `tools->env` and updates the value of the "SHLVL" variable, which represents 
 * the shell level.
 * If the "SHLVL" variable is found, its value is incremented. If it is not 
 * found, the function adds "SHLVL=1" to the environment representing the first 
 * shell.
 *
 * @param tools A pointer to a `t_tools` structure containing the environment 
 * variables.
 */
void	update_env(t_tools *tools)
{
	int			i;
	size_t		lvl;
	char		*new_lvl;
	char		*pre_lvl;
	int			flag;

	i = 0;
	flag = 0;
	lvl = 0;
	while (tools->env[i])
	{
		if (strncmp("SHLVL", tools->env[i], 5) == 0)
		{
			flag = 1;
			get_new_var_value(&pre_lvl, tools->env[i]);
			handle_shlvl(pre_lvl, &new_lvl, lvl);
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("SHLVL=", new_lvl);
			free(pre_lvl);
			free(new_lvl);
		}
		i++;
	}
	if (!flag)
		export_variable_to_env(tools, "SHLVL=1");
}

/**
 * @brief Extracts and returns the name of the machine from the 
 * "SESSION_MANAGER" environment variable.
 *
 * This function retrieves the value of the "SESSION_MANAGER" environment 
 * variable, parses it to extract a specific portion of the string, and returns 
 * this extracted name. If the "SESSION_MANAGER" variable is not found, it
 * returns an empty string.
 *
 * @param tools A pointer to a `t_tools` structure. This parameter is currently 
 * unused.
 * @param env An array of environment variables.
 *
 * @return A dynamically allocated string containing the extracted name from the
 * "SESSION_MANAGER" variable.
 * If the variable is not found, returns a dynamically allocated empty string so
 * it doesn't seg fault because being empty will ensure that it still exists.
 */
char	*get_name(t_tools *tools, char **env)
{
	char	*var;
	char	*name;
	int		i;

	(void)tools;
	var = get_var_from_env(env, "NAME");
	if (var)
		return (var);
	else
	{
		var = get_var_from_env(env, "SESSION_MANAGER");
		if (!var)
			return (ft_strdup(""));
		i = find_char_position(var, '/');
		name = ft_substr (var, i + 1, find_next_char_position(var, i, '.') 
				- i - 1);
		free(var);
	}
	return (name);
}

/**
 * @brief Initializes and configures the `tools` structure with environment 
 * variables and other default values.
 *
 * This function takes a pointer to a `t_tools` structure and an array of 
 * environment variables, initializes the `tools` structure with various 
 * environment-related values, and sets default values for several other members
 * of the structure. It also handles error cases where environment variables
 * are missing and prints an error message if memory allocation fails.
 * 
 * @param tools A pointer to a `t_tools` structure that will be initialized and 
 * configured.
 * @param envp An array of environment variables, typically passed from the main
 * function.
 */
void	config_tools(t_tools *tools, char **envp)
{
	ft_memset(tools, 0, sizeof(t_tools));
	tools->env = get_env(envp);
	tools->path = get_path(tools, tools->env);
	tools->pwd = get_pwd(tools, tools->env);
	tools->oldpwd = get_var_from_env(tools->env, "OLDPWD");
	tools->user = get_var_from_env(tools->env, "USER");
	if (!tools->user)
		tools->user = get_source_user_var(tools);
	tools->name = get_name(tools, tools->env);
	tools->home = get_var_from_env(tools->env, "HOME");
	if (tools->home == NULL)
		tools->home = get_source_home_var(tools, "/home/");
	if (!tools->path && !tools->pwd && !tools->home)
	{
		ft_putstr_fd("Error: Failed to allocate memory for tools\n",
			STDERR_FILENO);
		return ;
	}
	tools->original_stdin = dup (STDIN_FILENO);
	tools->original_stdout = dup (STDOUT_FILENO);
	update_env(tools);
}
