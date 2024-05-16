/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/16 20:44:42 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	sig_pipex_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 901;
		rl_replace_line("", 1);
		rl_on_new_line();
		// exit(EXIT_SUCCESS);
	}
	return ;
}

void	sig_pipex_handler_exit(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 901;
		// rl_replace_line("", 1);
		// rl_on_new_line();
		exit(EXIT_SUCCESS);
	}
	return ;
}


void	handle_pipex_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_pipex_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction (SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
