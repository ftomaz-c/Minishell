#include "../../includes/minishell.h"

char	**handle_home_abreviation(t_tools *tools, char **str)
{
	char	*home_var;
	int		home_var_len;
	char	*tmp;

	home_var = get_var_from_env(tools->env, "HOME");
	if (!home_var)
		return (str);
	home_var_len = ft_strlen(home_var);
	if (ft_strncmp(home_var, str[6], home_var_len) == 0)
	{
		tmp = ft_substr(str[6], home_var_len, ft_strlen(str[6]) - home_var_len);
		free(str[6]);
		str[6] = ft_strjoin("~", tmp);
		free(tmp);
	}
	free(home_var);
	return (str);
}

char	**generate_prompt(t_tools *tools)
{
	char	**str;

	str = calloc(10, sizeof (char *));
	if (!str)
		return (NULL);
	str[0] = ft_strdup("\033[1;32m");
	str[1] = ft_strdup(tools->user);
	str[2] = ft_strdup("@");
	str[3] = ft_strdup(tools->name);
	str[4] = ft_strdup("\033[0m:");
	str[5] = ft_strdup("\033[1;34m");
	str[6] = ft_strdup(tools->pwd);
	str[7] = ft_strdup("\033[0m");
	str[8] = ft_strdup("$ ");
	if (ft_strlen(str[1]) == 0)
	{
		free(str[1]);
		str[1] = ft_strdup("guest");
	}
	str = handle_home_abreviation(tools, str);
	return (str);
}

char	*prompt_line(t_tools *tools)
{
	char	*line;
	char	*prompt;
	char	**str;
	char	*tmp;
	int		i;

	str = generate_prompt(tools);
	if (!str)
		return (NULL);
	i = 0;
	prompt = ft_strdup("");
	while (str[i])
	{
		tmp = ft_strjoin(prompt, str[i]);
		free(prompt);
		free(str[i]);
		prompt = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	free(str);
	line = readline(prompt);
	free(prompt);
	return (line);
}
