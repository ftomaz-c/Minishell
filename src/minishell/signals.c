#include "../../includes/minishell.h"

void	ignore_sig_handler(int sig)
{
	(void)sig;
	//printf("\nignore\n");
	//if (sig == SIGINT)
	//	printf("\n");
}

void	react_sig_handler(int sig)
{
	//printf("\nreact\n");
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	handle_sigaction(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction (SIGQUIT, &sa, NULL);
}
