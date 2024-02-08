#include "../includes/minishell.h"

// int	pwd(t_tools *tools, t_parser **command)
int	pwd()
{
	char	buf[1024];

	// (void)tools;
	// (void)command;
	// printf("%s\n", getcwd(buf, sizeof(buf)));
	// chdir("..");
	return (printf("%s\n", getcwd(buf, sizeof(buf))));
}
// int	cd(t_tools *tools, t_parser **command)
int	cd(char *tools, char **command)
{
	// char	new_dir[1024];

	(void)tools;
	// (void)command;

// -----------------------------------------------------------------
// -------   delete this section after parser is done      -------
// -----------------------------------------------------------------

	// char *oldpwd = NULL;
	// char *pwd = NULL;

	// oldpwd = (char *)malloc(sizeof(char) * (strlen("/home/crebelo-") + 1));
	// pwd = (char *)malloc(sizeof(char) * (strlen("/home/crebelo-/Minishell") + 1));
	// strcpy(oldpwd, "/home/crebelo-");
	// strcpy(pwd, "/home/crebelo-/Minishell");

	// printf("olddir before: %s\n", oldpwd);
	// printf("curdir before: %s\n", pwd);

// -----------------------------------------------------------------
// -----------------------------------------------------------------

	// ELSE command only has more than 2 line -- too many args
	// printf("command[2]: %s\n", command[2]);
	// IF command only has 1 line -- means it's just cd
	// ELSE IF command only has 2 line -- means it's cd + path
	// printf("command is %s\n", command[2]);
	if (command && !command[1])
	{
		if (chdir("..") == 0)
		{
			printf("here\n");
			// free(tools.oldpwd);
			// // free(oldpwd);

			// tools.oldpwd = tools.pwd;
			// // oldpwd = pwd;

			// tools.pwd = getcwd(new_dir, sizeof(new_dir));
			// pwd = getcwd(new_dir, sizeof(new_dir));
		}
		else
			perror("cd: no such file or directory: ..");
	}
	else if (command && command[1])
	{
		if (chdir(command[1]) == 0)
		{
			// free(tools.oldpwd);
			// // free(oldpwd);

			// tools.oldpwd = tools.pwd;
			// // oldpwd = pwd;

			// tools.pwd = getcwd(new_dir, sizeof(new_dir));
			// pwd = getcwd(new_dir, sizeof(new_dir));
		}
		else
			printf("cd: no such file or directory: %s\n", command[1]);
	}
	else
	{	
		printf("here\n");
		return (printf("cd: too many arguments\n"));
	}

	// printf("olddir after: %s\n", oldpwd);
	// printf("curdir after: %s\n", pwd);

	return (1);
}
