/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 18:54:58 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 *     __  __   _           _   _____   _              _   _
 *    |  \/  | (_)         (_) /  ___| | |            | | | |
 *    | \  / |  _   _ __    _  \ `--.  | |___    ___  | | | |
 *    | |\/| | | | | '_ \  | |  `--. \ | '_  \  / _ \ | | | |
 *    | |  | | | | | | | | | | /\__/ / | | | | |  __/ | | | |
 *    |_|  |_| |_| |_| |_| |_| \____/  |_| |_|  \___| |_| |_|
 * 
 * MiniShell: A Minimalistic Shell
 *
 * Overview:
 * MiniShell is a simplified shell designed to mimic the functionality of the
 * Bourne-Again Shell (Bash).
 *
 * Key Features:
 * - Display a prompt when waiting for a new command;
 * - Have a working history;
 * - Search and launch the right executable (based on the PATH variable or using
 * a relative or an absolute path);
 * - Avoid using more than one global variable to indicate a received signal.
 * - Handle single quotes (') and double quotes (");
 * - Implement redirections;
 * - Implement pipes (| character). The output of each command in the pipeline
 * is connected to the input of the next command via a pipe;
 * - Handle environment variables ($ followed by a sequence of characters);
 * - Handle $? which should expand to the exit status of the most recently
 * executed;
 * - Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
 * - Implement the following builtins:
 *		- echo with option -n;
 *		- cd with only a relative or absolute path;
 *		- pwd with no options;
 *		- export with no options;
 *		- unset with no options;
 *		- env with no options or arguments;
 *		- exit with no options.
 *
 * Note:
 * - The readline() function can cause memory leaks.
 */
int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	char	*line;

	config_tools(&tools, envp);
	update_history(&tools, ".minishell_history");
	error_check(argc, argv);
	while (1)
	{
		line = NULL;
		tools.original_stdin = dup (STDIN_FILENO);
		tools.original_stdout = dup (STDOUT_FILENO);
		handle_sigaction();
		if (!isatty(STDIN_FILENO))
			non_interactive_mode(&tools, line);
		else
			interactive_mode(&tools, line);
		if (tools.exit)
			break ;
	}
	free_and_exit(&tools, global_status()->nbr);
	return (global_status()->nbr);
}
