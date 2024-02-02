/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:37:33 by ftomazc           #+#    #+#             */
/*   Updated: 2024/02/02 15:29:25 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	update_history();
	(void)envp;
	while (1)
	{
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		add_history_file(line);
		free(line);   
	}
	return (0);
}