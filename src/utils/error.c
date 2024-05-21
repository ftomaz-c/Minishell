/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/19 21:17:39 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/**
 * @brief Checks for incorrect command-line arguments and
 * displays an error message if found.
 * 
 * This function checks if the number of command-line
 * arguments is not equal to 1.
 * If incorrect arguments are provided, it displays an error
 * message and usage information,
 * then exits the program with EXIT_FAILURE.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 */
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
