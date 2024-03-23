#include "../../../includes/builtins.h"

void	export_err(int err, char *str)
{
	if (err == 1)
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	g_status = err;
}

/**
 * @brief Get the new variable value from the input string.
 * 
 * This function extracts the new variable value from the input string.
 * 
 * @param var Pointer to the destination string where the value will be stored.
 * @param str Input string containing the variable and its value.
 * 
 * @note This function allocates memory for the new value string.
 */
void	get_new_var(char **var, char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	*var = ft_calloc(sizeof(char *), i + 1);
	if (!var)
		return ;
	(*var) = ft_strcpy(*var, str);
}

/**
 * @brief Copy the environment variable to a new array.
 * 
 * This function copies the environment variable to a new array.
 * 
 * @param tools Pointer to the tools structure containing environment variables.
 * @param new_array Pointer to the new array where the variable will be copied.
 * @param var_value Value of the variable to copy.
 * @param i Index to start copying.
 * 
 * @return Returns 1 if successful, otherwise returns 0.
 * 
 * @note This function assumes that the new 
 * array is large enough to hold the copied variable.
 *       It also frees the memory allocated for the old value.
 */

int	copy_var_to_env(t_tools *tools, char **array, char *var_value, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		array[j] = ft_strdup(tools->env[j]);
		if (array[j] == NULL)
		{
			free_list(array);
			free(var_value);
			return (0);
		}
		j++;
	}
	array[j] = ft_strdup(var_value);
	if (array[j] == NULL)
	{
		free_list(array);
		free(var_value);
		return (0);
	}
	return (1);
}
