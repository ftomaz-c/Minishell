#include "../../includes/builtins.h"

int	count_lines(char **list)
{
	int	line_count;
	
	line_count = 0;
	while (list[line_count])
		line_count++;
	return (line_count);
}

int	unset(t_tools *tools, t_parser *command)
{
	char 	**new_env;
	int		i;
	int		j;

	new_env = ft_calloc(count_lines(tools->env) + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(command->str[1], tools->env[i], ft_strlen(command->str[1])) != 0)
		{
			new_env[j] = ft_strdup(tools->env[i]);
			if (!new_env[j])
			{
				free_list(new_env);
				return (1);
			}
			j++;
		}
		i++;
	}
	free_list(tools->env);
	tools->env = new_env;
	return (0);
}
