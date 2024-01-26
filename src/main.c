/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:37:33 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/26 15:00:34 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (line && *line)
			add_history_file(line);
		free(line);   
	}
	return (0);
}