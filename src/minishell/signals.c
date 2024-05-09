#include "../../includes/minishell.h"

void	ignore_sig_handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		printf("\n");
	// if (sig == SIGQUIT)
	// 	return ;
}

void	react_sig_handler(int sig)
{
	
	if (sig == SIGINT)
	{
		if (!isatty(STDIN_FILENO))
		{
			printf("\n");
			ft_putstr_fd(".minishell: ", STDOUT_FILENO);
		}
		else
		{
			printf("\n");
			rl_replace_line("", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	// if (sig == SIGQUIT)
	// 	return ;
}

void	handle_sigaction(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
