#include "../../includes/builtins.h"

void	update_env_vars(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (strncmp("PWD", tools->env[i], 3) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("PWD=", tools->pwd);
		}	
		else if (strncmp("OLDPWD", tools->env[i], 6) == 0)
		{
			free(tools->env[i]);
			tools->env[i] = ft_strjoin("OLDPWD=", tools->oldpwd);			
		}
		i++;
	}
}

int	cd_no_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];
	char	*home_var;

	(void)command;
	home_var = tools->home;
	if (ft_strcmp(tools->pwd, home_var) != 0)
	{	
		if (chdir(home_var) == 0)
		{
			free(tools->oldpwd);
			tools->oldpwd = ft_strdup(tools->pwd);
			free(tools->pwd);
			tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
		}
		else
			return(printf("cd: no such file or directory: .."));
	}
	free(home_var);
	return (0);
}

int	cd_handle_specific_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];

	if (chdir(command->str[1]) == 0)
	{
		free(tools->oldpwd);
		tools->oldpwd = ft_strdup(tools->pwd);
		free(tools->pwd);
		tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
	}
	else
		return(printf("cd: no such file or directory: %s\n", command->str[1]));
	return (0);
}

int	cd_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];

	if (ft_strcmp(command->str[1], "..") == 0)
	{
		if (chdir("..") == 0)
		{
			free(tools->oldpwd);
			tools->oldpwd = ft_strdup(tools->pwd);
			free(tools->pwd);
			tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
		}
		else
			return(printf("cd: no such file or directory: .."));
	}
	else if (ft_strcmp(command->str[1], ".") == 0)
		return (0);
	else
		return(cd_handle_specific_path(tools, command));
	return (0);
}

int	cd(t_tools *tools, t_parser *command)
{
	if (command && !command->str[1])
		cd_no_path(tools, command);
	else if (command && command->str[1] && !command->str[2])
		cd_path(tools, command);
	else
		return(printf("cd: too many arguments\n"));
	update_env_vars(tools);
	return (0);
}
