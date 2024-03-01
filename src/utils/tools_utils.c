#include "../../includes/minishell.h"

int	compare_var_to_env(char *env, char *var)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] && var[i])
	{
		if (env[i] == var[i])
			i++;
		else
			return (0);
	}
	if (var[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

/**
 * @brief Frees the memory allocated for the tools structure.
 * 
 * This function frees the memory allocated for the tools
 * structure, including its
 * environment variables, path list, current working directory,
 * and previous working directory.
 * 
 * @param tools A pointer to the tools structure.
 * 
 * @return None.
 * 
 * @note Assumes the tools structure is properly initialized.
 * 
 * @see config_tools
 * 
 * @warning Make sure to call this function to avoid memory leaks
 * after using the tools structure.
 * 
 */

void	free_tools(t_tools *tools)
{
	free_list(tools->env);
	free_list(tools->path);
	free(tools->pwd);
	free(tools->oldpwd);
	free(tools->home);
	free(tools->user);
	free(tools->name);
}