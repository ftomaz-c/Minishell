/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:08:17 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/31 10:32:21 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_check(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		printf("Error: This program does not accept arguments\n");
		printf("Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
}