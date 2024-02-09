#include "../../includes/builtins.h"

int	echo(t_tools *tools, t_parser *command)
{
	int	i;

	i = 1;
	(void)tools;
	while (command->str[i])
	{
		if (ft_strncmp(command->str[i], "-n", ft_strlen(command->str[i])) == 0)
		{
			i++;
			while (command->str[i])
			{
				printf("%s", command->str[i]);
				if (command->str[i + 1])
					printf(" ");
				i++;
			}
		}
		else
		{
			while (command->str[i])
			{
				printf("%s", command->str[i]);
				if (command->str[i + 1])
					printf(" ");
				i++;
			}
			printf("\n");	
		}
	}
	return (0);
}