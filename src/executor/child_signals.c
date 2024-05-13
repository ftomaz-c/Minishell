#include "../../includes/executor.h"

void	sig_pipex_handler(int sig)
{
	if (sig == SIGINT)
		g_status = 901;
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
