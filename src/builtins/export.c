#include "../../includes/builtins.h"

void	sort_print_env(t_tools *tools)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = get_env_export(tools->env, i);
	sort_array(env_copy);
	while (env_copy[i])
	{	
		if (ft_strncmp(env_copy[i], "declare -x _=", 13) == 0)
			i++;
		else
			printf("%s\n", env_copy[i++]);
	}
	free_list(env_copy);
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

void	export_variable_to_env(t_tools *tools, char *str)
{
	int		i;
	char	*var_value;
	char	**new_array;

	i = 0;
	var_value = NULL;
	get_new_var(&var_value, str);
	while (tools->env[i])
		i++;
	new_array = ft_calloc(sizeof(char *), i + 2);
	if (new_array == NULL)
		return;
	if (!copy_var_to_env(tools, new_array, var_value, i))
		return ;
	free(var_value);
	free_list(tools->env);
	tools->env = new_array;	
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
	copy_var_name(var_path, str, i);
	if (check_var_path(tools->env, var_path))
	{
		substitute_env_var_value(tools, var_path, str);
		return (1);
	}
	free(var_path);
	return (0);
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
