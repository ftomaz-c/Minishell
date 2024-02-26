#include "../../includes/builtins.h"

int	pwd(t_tools *tools, t_parser *command)
{
	char	buf[1024];

	(void)tools;
	(void)command;
	printf("%s\n", getcwd(buf, sizeof(buf)));
	global_status = EXIT_SUCCESS;
	return (global_status);
}
