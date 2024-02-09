#include "../../includes/builtins.h"

int	pwd(t_tools *tools, t_parser *command)
{
	char	buf[1024];

	(void)tools;
	(void)command;
	return (printf("%s\n", getcwd(buf, sizeof(buf))));
}
