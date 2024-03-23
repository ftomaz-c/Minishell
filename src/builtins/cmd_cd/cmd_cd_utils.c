#include "../../../includes/builtins.h"
/**
 * @brief Updates the environment variables PWD and OLDPWD 
 * with the current and previous working directories.
 * 
 * This function updates the environment variables PWD and 
 * OLDPWD with the current and previous working directories, respectively.
 * 
 * @param tools Pointer to the tools struct containing necessary information.
 * 
 * @note This function assumes the validity of the tools struct.
 * 
 * @warning Behavior is undefined if tools is NULL.
 * 
 * @see strncmp, ft_strjoin
 * 
 * @example
 * ```
 * // Example usage of update_env_vars function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * update_env_vars(tools); // Update environment
 * variables PWD and OLDPWD
 * ```
 */

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

void	cd_err(int err, char *str, char root)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!(root == '/'))
		ft_putstr_fd("cd: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (err == 1)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (err == 2 || err == 3)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (err == 13)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (err == 20)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else if (err == 0 || err == 25)
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else if (err == 36)
		ft_putstr_fd(": File name too long\n", STDERR_FILENO);
	g_status = EXIT_FAILURE;
}

int	cd_handle_slash_path(t_tools *tools)
{
	if (chdir(tools->oldpwd) == 0)
	{
		printf("%s\n", tools->oldpwd);
		free(tools->pwd);
		tools->pwd = ft_strdup(tools->oldpwd);
		free(tools->oldpwd);
		tools->oldpwd = get_var_from_env(tools->env, "PWD");
		return (EXIT_SUCCESS);
	}
	else
		cd_err(2, tools->oldpwd, 0);
	return (EXIT_SUCCESS);
}

int	cd_handle_dot_path(t_tools *tools)
{
	char	*tmp;

	if (chdir(tools->pwd) == 0)
		return (EXIT_SUCCESS);
	else
	{	
		cd_err(3, "error retrieving current directory: getcwd: cannot access parent directories", 0);
		tmp = ft_strdup(tools->pwd);
		free(tools->pwd);
		tools->pwd = ft_strjoin(tmp, "/.");
		free(tmp);
		return (EXIT_SUCCESS);
	}
}