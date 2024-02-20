#include "../../includes/builtins.h"

int	count_lines(char **list)
{
	int	line_count;
	
	line_count = 0;
	while (list[line_count])
		line_count++;
	return (line_count);
}

int	check_var(t_tools *tools, char *str)
{
	char	*var_path;
	int		equal_pos;
	int		i;
	int		size;

	i = 0;
	equal_pos = find_char_position(str, '=');
	size = 0;
	while (str[i] && i < equal_pos)
	{
		if (str[i] == '\"' || str[i] == '\'')
			size++;
		i++;
	}
	var_path = ft_calloc(sizeof(char *), (i - size) + 1);
	if (!var_path)
		return (1);
	copy_var_name(var_path, str, i);
	if (check_var_path(tools->env, var_path))
	{
		free(var_path);
		return (1);
	}
	free(var_path);
	return (0);
}

void	unset_var_from_env(t_tools *tools, char *str, int i)
{
	int		j;
	char 	**new_env;
	int		equal_pos;

	new_env = ft_calloc(count_lines(tools->env) + 1, sizeof(char *));
	if (!new_env)
		return ;
	j = 0;
	while (tools->env[i])
	{
		equal_pos = find_char_position(tools->env[i], '=');
		if (ft_strncmp(str, tools->env[i], equal_pos) != 0)
		{
			new_env[j] = ft_strdup(tools->env[i]);
			if (!new_env[j])
			{
				free_list(new_env);
				return ;
			}
			j++;
		}
		i++;
	}
	free_list(tools->env);
	tools->env = new_env;
}

int	unset(t_tools *tools, t_parser *command)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	if(!command->str[i])
		printf("\n");
	while (command->str[i])
	{
		if (check_var(tools, command->str[i]))
			unset_var_from_env(tools, command->str[i], pos);
		i++;
	}
	return (0);
}
