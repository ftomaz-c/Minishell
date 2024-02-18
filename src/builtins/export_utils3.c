#include "../../includes/builtins.h"

int	ft_isalpha_plus_underscore(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	find_char_position(char *str, char c)
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

void	copy_var(char *var_path, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < (int)ft_strlen(str))
	{
		if (str[j] == '\'' || str[j] == '\"')
			j++;
		else
		{
			var_path[i] = str[j];
			i++;
			j++;
		}
	}
}

void	get_new_var(char **var, char *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			size++;
		i++;
	}
	*var = ft_calloc(sizeof(char *), (i - size) + 1);
	if (!var)
		return ;
	copy_var(*var, str);
}

int	copy_var_to_env(t_tools *tools, char **new_array, char *var_value, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_array[j] = ft_strdup(tools->env[j]);
		if (new_array[j] == NULL)
		{
			free_list(new_array);
			free(var_value);
			return (0);
		}
		j++;
	}
	new_array[j] = ft_strdup(var_value);
	if (new_array[j] == NULL)
	{
		free(var_value);
		free_list(new_array);
		return (0);
	}
	return (1);
}
