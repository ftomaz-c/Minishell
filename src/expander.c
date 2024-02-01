#include "../includes/minishell.h"

void	expander(char **list, char **env)
{
	int		index;
	char	*var;
	char	*value;

	index = 0;
	while(list[index])
	{
		if (list[index][0] == '$')
		{
			var = ft_substr(list[index], 1, strlen(list[index]) - 1);
			value = get_var_from_env(env, var);
			free(var);
			free(list[index]);
			if (value == NULL)
				list[index] = ft_strdup("");
			else
				list[index] = ft_strdup(value);
			free(value);
		}
		index++;
	}
}
