#include "../../includes/builtins.h"
void	substitute_env_var_value(t_tools *tools, char *var_path, char *str);
void	copy_var_name(char *var_path, char *str, int equal_pos);
int		find_char_position(char *str, char c);

void	free_env(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}
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
	{
		var_value[0] = '\"';
		var_value[1] = '\"';
		var_value[2] = '\0';
	}
	else
		copy_var_value_quotes(var_value, str, equal_pos + 1);
	new_path = ft_strjoin(var_path, var_value);
	free(var_path);
	free(var_value);
	return (new_path);
}

char	**get_env_export(char **envp)
{
	char	**env;
	int		count;
	int		index;
	char	*tmp;

	count = 0;
	while (envp[count])
		count++;
	env = ft_calloc(sizeof(char *), count + 1);
	if (env == NULL)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		tmp = prepare_var(envp[index]);
		env[index] = ft_strjoin("declare -x ", tmp);
		free(tmp);
		if (env[index] == NULL)
			return (NULL);
		index++;
	}
	return (env);
}

void	sort_print_env(t_tools *tools)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = get_env_export(tools->env);
	sort_array(env_copy);
	while (env_copy[i])
		printf("%s\n", env_copy[i++]);
	free_env(env_copy);
}

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

int	check_valid_export(char *parser)
{
	int	i;
	int	equal_pos;

	i = 0;
	if (parser[0] == '\"' || parser[0] == '\'')
		i++;
	if (ft_strcmp(parser,"=") == 0 || parser[i] == '=' || !ft_isalpha_plus_underscore(parser[i]))
	{	
		printf("bash: export: `%s': not a valid identifier\n", parser);
		return (0);
	}
	i = 1;
	equal_pos = find_char_position(parser, '=');
	while (parser[i] && i < equal_pos)
	{
		if (parser[i] != '_' && parser[i] != '\"' && parser[i] != '\'' && !ft_isalnum(parser[i]))
		{
			printf("bash: export: `%s': not a valid identifier\n", parser);
			return (0);
		}
		i++;
	}
	return (1);
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
		{	
			j++;
			var_path[i] = str[j];
		}
		else
			var_path[i] = str[j];
		i++;
		j++;
	}
}

int check_var_path(char **env, char *var)
{
	int		index;

	index = 0;
	while (var && env[index])
	{
		if (!ft_strncmp(var, env[index], (int)ft_strlen(var)))
			return (1);
		index++;
	}
	return (0);
}


int	check_if_var_exists(t_tools *tools, char *str)
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
	copy_var_name(var_path, str, equal_pos);
	if (!check_var_path(tools->env, var_path))
	{	
		free(var_path);
		return (0);
	}
	substitute_env_var_value(tools, var_path, str);
	free(var_path);
	return (1);
}

void	copy_var_value(char *var_path, char *str, int start)  // add flag to use same function as above
{
	int	i;

	// i = 1;
	i = 0;
	while (start < (int)ft_strlen(str))
	{
		// if (!var_path[0])
		// 	var_path[0] = '\"';
		if (str[start] == '\'' || str[start] == '\"')
			start++;
		if (start >= (int)ft_strlen(str))
			break ;
		var_path[i] = str[start];
		i++;
		start++;
	}
	// var_path[i] = '\"';
	// var_path[++i] = '\0';
	var_path[i] = '\0';
}

void	get_new_var_value(char **var_value, char *str)
{
	int		start;
	int		i;
	int		size;

	i = find_char_position(str, '=') + 1;
	start = i;
	size = 0;
	while (i < (int)ft_strlen(str))
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

	i = 0;
	var_value = NULL;
	get_new_var_value(&var_value, str);
	while (tools->env[i])
	{
		if (var_path && strncmp(var_path, tools->env[i], (int)ft_strlen(var_path)) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strjoin(var_path, var_value);
			break ;
		}
		i++;
	}
	free(var_value);
	free(var_path);
}
void	add_var_to_env(t_tools *tools, char *var_path, char *str)
{
	int		i;
	int		j;
	char	*var_value;
	char	**new_array;

	i = 0;
	var_value = NULL;
	get_new_var_value(&var_value, str);
	while (tools->env[i])
		i++;
	new_array = ft_calloc(sizeof(char *), i + 2);
	if (new_array == NULL)
		return;
	j = 0;
	while (j < i)
	{
		new_array[j] = ft_strdup(tools->env[j]);
		if (new_array[j] == NULL)
		{
			free_env(new_array);
			free(var_value);
			return;
		}
		j++;
	}
	new_array[i] = ft_strjoin(var_path, var_value);
	if (new_array[i] == NULL)
	{
		free_env(new_array);
		return;
	}
	free(var_value);
	free_env(tools->env);
	tools->env = new_array;	
}

void	export_variable_to_env(t_tools *tools, char *str)
{
	char	*var_path;
	int		equal_pos;
	int		i;
	int		size;

	i = 0;
	equal_pos = find_char_position(str, '=');
	size = 0;
	while (i <= equal_pos)
	{
		if (str[i] == '\"' || str[i] == '\'')
			size++;
		i++;
	}
	var_path = ft_calloc(sizeof(char *), (i - size) + 1);
	if (!var_path)
		return ;
	copy_var_name(var_path, str, equal_pos);
	add_var_to_env(tools, var_path, str);
	free(var_path);
}

int	export(t_tools *tools, t_parser *parser)
{
	int	i;

	i = 1;
	if (!parser->str[1])
		sort_print_env(tools);
	else
	{
		while (parser->str[i])
		{
			if (check_valid_export(parser->str[i]))
			{
				if (check_if_var_exists(tools, parser->str[i]))
					i++;
				else
				{	
					export_variable_to_env(tools, parser->str[i]);
					i++;
				}
			}
			else
				i++;
		}
	}
	return(0);
}
