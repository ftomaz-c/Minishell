#include "../../includes/minishell.h"

void	handle_shlvl(char *pre_lvl, char **new_lvl, size_t lvl)
{
	if (!pre_lvl)
		lvl = 1;
	else
		lvl = ft_atoll(pre_lvl);
	if ((int)lvl < 0)
		*new_lvl = ft_itoa(0);
	else
		*new_lvl = ft_itoa(lvl + 1);
	if (ft_atoll(*new_lvl) > 1000)
	{	
		*new_lvl = ft_itoa(1);
		ft_putstr_fd("bash: warning: shell level (", STDERR_FILENO);
		ft_putstr_fd(ft_itoa(lvl + 1), STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to ", STDERR_FILENO);
		ft_putstr_fd(*new_lvl, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	update_env(t_tools *tools)
{
	int			i;
	size_t		lvl;
	char		*new_lvl;
	char		*pre_lvl;
	int			flag;

	i = 0;
	flag = 0;
	lvl = 0;
	while (tools->env[i])
	{
		if (strncmp("SHLVL", tools->env[i], 5) == 0)
		{
			flag = 1;
			get_new_var_value(&pre_lvl, tools->env[i]);
			handle_shlvl(pre_lvl, &new_lvl, lvl);
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("SHLVL=", new_lvl);
			free(pre_lvl);
			free(new_lvl);
		}
		i++;
	}
	if (!flag)
		export_variable_to_env(tools, "SHLVL=1");
}

/**
 * @brief Configures the tools structure with environment information.
 * 
 * This function configures the tools structure with environment information,
 * including environment variables, the PATH variable,
 * current working directory,
 * and previous working directory.
 * 
 * @param tools A pointer to the tools structure to be configured.
 * @param envp The array of environment variables.
 * 
 * @return 1 on success, 0 on failure.
 * 
 * @note The tools structure must be properly initialized before calling
 * this function.
 * 
 * @see free_tools
 * 
 * @warning Make sure to check the return value for failure.
 * 
 * @example
 * 
 * ```
 * t_tools tools;
 * if (config_tools(&tools, envp)) {
 *     // Use tools...
 * } else {
 *     printf("Failed to configure tools\n");
 * }
 * ```
 */

char	*get_source_home_var(char *str)
{
	int	fd;
	char	**passwd;
	int	nlines;
	int	index;
	char	*line;

	index = 0;
	nlines = count_lines_in_file("/etc/passwd");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		printf("couldn't open\n");
	passwd = ft_calloc(sizeof(char **), nlines + 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		passwd[index] = ft_strdup(line);
		free(line);
		index++;
	}
	int	end = 0;
	int	len = ft_strlen(passwd[index - 2]) - 1;
	while (len > 0 && passwd[index - 2][len])
	{
		if (passwd[index - 2][len] == ':')
		{
			end = len;
			len--;
			while (len > 0 && passwd[index - 2][len] != ':')
				len--;
			if (passwd[index - 2][len] == ':')
				break ;
		}
		len--;
	}
	char *home = ft_substr(passwd[index - 2], len + 1, end - len -1);
	free_list(passwd);
	close(fd);
	return (home);
}

int	config_tools(t_tools *tools, char **envp)
{
	tools->env = get_env(envp);
	tools->path = get_path(tools->env);
	if (tools->path == NULL)
		return (0);
	tools->pwd = get_var_from_env(tools->env, "PWD");
	if (tools->pwd == NULL)
		return (0);
	tools->oldpwd = get_var_from_env(tools->env, "OLDPWD");
	if (tools->oldpwd == NULL)
		return (0);
	tools->home = get_var_from_env(tools->env, "HOME");
	if (tools->home == NULL)
	{	
		// tools->home = get_source_home_var("/etc/passwd");
		if (!tools->home)
			return (0);
	}
	tools->user = get_var_from_env(tools->env, "USER");
	if (tools->user == NULL)
		return (0);
	tools->name = get_var_from_env(tools->env, "NAME");
	if (tools->name == NULL)
		return (0);
	tools->pipes = 0;
	tools->parser = NULL;
	tools->exit = 0;
	update_env(tools);
	return (1);
}
