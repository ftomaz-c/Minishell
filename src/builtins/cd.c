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
		//else
		//	return(printf("cd: no such file or directory: .."));
	}
	return (0);
}

void	cd_err(int err, char *str)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (err == 1)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (err == 2)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (err == 3)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else if (err == 4)
		ft_putstr_fd(": File name too long\n", STDERR_FILENO);
	else if (err == 5)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	global_status = EXIT_FAILURE;
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
	else if ((chdir(command->str[1]) < 0) && command->str[1][0])
	{
		if (errno == 2)
			cd_err(2, command->str[1]);
		if (errno == 20)
			cd_err(3, command->str[1]);
		if (errno == 36)
			cd_err(4, command->str[1]);
		if (errno == 13)
			cd_err(5, command->str[1]);
	}
	return (global_status);
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
			cd_err(2, command->str[1]);
	}
	else if (ft_strcmp(command->str[1], ".") == 0)
		return (EXIT_SUCCESS);
	else
		return(cd_handle_specific_path(tools, command));
	return (EXIT_SUCCESS);
}

int	cd(t_tools *tools, t_parser *command)
{
	if ((command && !command->str[1]) || ft_strcmp(command->str[1], "~") == 0)
		cd_no_path(tools, command);
	else if (command && command->str[1] && !command->str[2])
		cd_path(tools, command);
	else
		cd_err(1, NULL);
	update_env_vars(tools);
	return (global_status);
}
