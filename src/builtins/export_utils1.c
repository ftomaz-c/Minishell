#include "../../includes/builtins.h"

void	sort_array(char **env_copy)
{
	int		i;	
	char	*tmp;

	i = 0;
	while (env_copy[i] && env_copy[i + 1])
	{
		tmp = env_copy[i];
		if (strcmp(env_copy[i], env_copy[i + 1]) > 0)
		{	
			env_copy[i] = env_copy[i + 1];
			env_copy[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

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

void	copy_var_name(char *var_path, char *str, int equal_pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && j <= equal_pos)
	{
		if ((str[j] == '\'' || str[j] == '\"') && str[j + 1])
			j++;
		else
		{
			var_path[i] = str[j];
			i++;
			j++;
		}
	}
}

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
	var_value = ft_calloc(sizeof(char *), (ft_strlen(str) - (equal_pos + 1)) + 3);
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

char	**get_env_export(char **envp, int i)
{
	char	**env;
	char	*tmp;

	while (envp[i])
		i++;
	env = ft_calloc(sizeof(char *), i + 1);
	if (env == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			tmp = prepare_var(envp[i]);
			env[i] = ft_strjoin("declare -x ", tmp);
			free(tmp);
			if (env[i] == NULL)
				return (NULL);
		}
		else
			env[i] = ft_strjoin("declare -x ", envp[i]);
		i++;
	}
	return (env);
}
