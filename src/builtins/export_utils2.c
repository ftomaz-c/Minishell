#include "../../includes/builtins.h"

int check_var_path(char **env, char *var)
{
	int		index;
	int		equal_pos;
	int		equal_pos_var;

	index = 0;
	equal_pos_var = find_char_position(var, '=');
	while (var && env[index])
	{
		equal_pos = find_char_position(env[index], '=');
		if (equal_pos < equal_pos_var)
			equal_pos = equal_pos_var;
		if (!ft_strncmp(env[index], var, equal_pos))
			return (1);
		index++;
	}
	return (0);
}

void	copy_var_value(char *var_path, char *str, int start)
{
	int	i;

	i = 0;
	if (start >= (int)ft_strlen(str))
	{
		var_path = NULL;
		return ;
	}
	while (start < (int)ft_strlen(str))
	{
		if (str[start] == '\'' || str[start] == '\"')
			start++;
		else
		{
			var_path[i] = str[start];
			i++;
			start++;
		}
	}
}

void	get_new_var_value(char **var_value, char *str)
{
	int		start;
	int		i;
	int		size;

	i = find_char_position(str, '=') + 1;
	if (i >= (int)ft_strlen(str))
	{
		*var_value = NULL;
		return ;
	}
	start = i;
	size = 0;
	while (str[i] && i < (int)ft_strlen(str))
	{
		if (str[i] == '\"' || str[i] == '\'')
			size++;
		i++;
	}
	*var_value = ft_calloc(sizeof(char *), (ft_strlen(str) - start - size) + 1); // change to use same as above;
	if (!var_value)
		return ;
	copy_var_value(*var_value, str, start);
}

void	substitute_env_var_value(t_tools *tools, char *var_path, char *str)
{
	int		i;
	char	*var_value;
	int		equal_pos;

	i = 0;
	get_new_var_value(&var_value, str);
	while (tools->env[i])
	{
		equal_pos = find_char_position(tools->env[i], '=');
		if (var_path && strncmp(tools->env[i], var_path , equal_pos) == 0)
		{
			free(tools->env[i]);
			if (!var_value)
				tools->env[i] = ft_strdup(var_path);
			else
				tools->env[i] = ft_strjoin(var_path, var_value);
			break ;
		}
		i++;
	}
	free(var_value);
	free(var_path);
}
