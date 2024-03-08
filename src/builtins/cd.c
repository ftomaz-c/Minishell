#include "../../includes/builtins.h"

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

/**
 * @brief Changes the current working directory to the user's home directory.
 * 
 * This function changes the current working directory
 *  to the user's home directory.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return 0 if the directory change is successful, 
 * otherwise prints an error message and returns 1.
 * 
 * @note This function assumes the validity of the tools struct.
 * 
 * @warning Behavior is undefined if tools is NULL.
 * 
 * @see chdir, printf, ft_strdup, getcwd
 * 
 * @example
 * ```
 * // Example usage of cd_no_path function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = cd_no_path(tools, command);
 * // Change directory to the home directory
 * // status will be 0 if the directory change is
 * successful, otherwise an error message will be printed.
 * ```
 */

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
/**
 * @brief Handles changing the current working 
 * directory to a specific path.
 * 
 * This function handles changing the current working directory 
 * to a specific path provided as an argument.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return 0 if the directory change is successful, otherwise 
 * prints an error message and returns 1.
 * 
 * @note This function assumes the validity of the tools struct
 *  and the presence of the directory path in command->str[1].
 * 
 * @warning Behavior is undefined if tools is NULL or if the 
 * directory path is not present.
 * 
 * @see chdir, printf, ft_strdup, getcwd
 * 
 * @example
 * ```
 * // Example usage of cd_handle_specific_path function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = cd_handle_specific_path(tools, command); 
 * // Change directory to a specific path
 * // status will be 0 if the directory change is successful, 
 * otherwise an error message will be printed.
 * ```
 */

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
		cd_err(errno, command->str[1], 0);
	return (g_status);
}

/**
 * @brief Handles changing the current working directory 
 * based on a provided path.
 * 
 * This function handles changing the current working
 * directory based on a provided path.
 * It supports changing to the parent directory ("..") and handling
 *  specific directory paths.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return 0 if the directory change is successful, otherwise
 *  prints an error message and returns 1.
 * 
 * @note This function assumes the validity of the tools struct and 
 * the presence of the directory path in command->str[1].
 * 
 * @warning Behavior is undefined if tools is NULL or if 
 * the directory path is not present.
 * 
 * @see chdir, printf, ft_strdup, getcwd
 * 
 * @example
 * ```
 * // Example usage of cd_path function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = cd_path(tools, command); // Change directory 
 * based on the provided path
 * // status will be 0 if the directory change is successful,
  otherwise an error message will be printed.
 * ```
 */

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


int	cd_path(t_tools *tools, t_parser *command)
{
	char	new_pwd[1024];

	if (ft_strcmp(command->str[1], "..") == 0)
	{
		if (chdir("..") == 0)
		{
			free(tools->oldpwd);
			tools->oldpwd = get_var_from_env(tools->env, "PWD");
			free(tools->pwd);
			tools->pwd = ft_strdup(getcwd(new_pwd, sizeof(new_pwd)));
		}
		else
			cd_err(errno, command->str[1], 0);
	}
	else if (ft_strcmp(command->str[1], "-") == 0)
		cd_handle_slash_path(tools);
	else if (ft_strcmp(command->str[1], ".") == 0)
		cd_handle_dot_path(tools);
	else
		return(cd_handle_specific_path(tools, command));
	return (EXIT_SUCCESS);
}
/**
 * @brief Handles the execution of the cd command, 
 * changing the current working directory.
 * 
 * This function handles the execution of the cd command, 
 * which changes the current working directory.
 * It supports changing to the home directory, parent 
 * directory (".."), and specific directory paths.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the cd command.
 * 
 * @note This function assumes the validity of the tools struct.
 * 
 * @warning Behavior is undefined if tools is NULL.
 * 
 * @see printf, global_status, update_env_vars
 * 
 * @example
 * ```
 * // Example usage of cd function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = cd(tools, command); // Execute the cd command
 * // status will be the global status after executing the cd command.
 * ```
 */

int	cd(t_tools *tools, t_parser *command)
{
	if (command && command->str[0][0] == '/')
	{
		chdir(command->str[0]);
		cd_err(errno, command->str[0], '/');
		if (errno == 2)
			g_status = 127;
		else if (errno == 25)
			g_status = 126;
		if (errno == 0)
			chdir(tools->pwd);
	}
	else if ((command && !command->str[1]) || ft_strcmp(command->str[1], "~") == 0)
		cd_no_path(tools, command);
	else if (command && command->str[1] && !command->str[2])
		cd_path(tools, command);
	else
		cd_err(1, NULL, 0);
	update_env_vars(tools);
	return (g_status);
}
