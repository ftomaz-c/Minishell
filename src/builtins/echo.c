#include "../../includes/builtins.h"
int	echo_n_flag(char **str, int	*pos)
{
	size_t	i;

	i = 0;
	if (ft_strncmp(str[*pos], "-n", 2) != 0)
		return (i);
	while(ft_strncmp(str[*pos], "-n", 2) == 0)
	{
		while (str[*pos][i] != ' ' && str[*pos][i])
			i++;
		if (i != ft_strlen(str[*pos]))
		{
			i = 0;
			break ;
		}
		(*pos)++;
	}
	return (i);
}

void	echo_print(t_parser *command, int pos, int flag)
{
	while (command->str[pos])
	{
		printf("%s", command->str[pos]);
		if (command->str[pos + 1])
			printf(" ");
		pos++;
	}
	if (!flag)
		printf("\n");
}

int	echo(t_tools *tools, t_parser *command)
{
	int	i;
	int	flag;

	i = 1;
	(void)tools;
	if (!command->str[i])
		printf("\n");
	else
	{
		flag = echo_n_flag(command->str, &i);
		echo_print(command, i, flag);
	}
	g_status = EXIT_SUCCESS;
	return (g_status);
}
