/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/14 15:29:12 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	echo_n_flag(char **str, int	*pos)
{
	size_t	i;

	i = 0;
	if (ft_strncmp(str[*pos], "-n", 2) != 0)
		return (i);
	while (str[*pos] && ft_strncmp(str[*pos], "-n", 2) == 0)
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
		printf(command->str[pos], 1);
		if (command->str[pos + 1])
			printf(" ");
		pos++;
	}
	if (!flag)
		printf("\n");
}

int	cmd_echo(t_tools *tools, t_parser *command)
{
	int			i;
	int			flag;
	t_parser	*cmd;

	i = 1;
	(void)tools;
	cmd = command;
	if (!cmd->str[i])
		printf("\n");
	else
	{
		flag = echo_n_flag(cmd->str, &i);
		echo_print(cmd, i, flag);
	}
	g_status = EXIT_SUCCESS;
	return (g_status);
}
