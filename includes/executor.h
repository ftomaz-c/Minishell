/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/24 17:11:34 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*src/executor/executor.c*/
void	exec_path(t_tools *tools, char **cmd_args, char **envp);
int		exec_builtins(t_tools *tools);
void	execute_cmd(t_tools *tools, t_parser *parser);
void	set_and_exec(t_tools *tools, t_parser *parser);
int		executor(t_tools *tools);

/*src/executor/executor_utils.c*/
void	broadcast_signal(t_tools *tools, int num_pids, int signal);
char	**basic_env(void);
void	free_and_exit(t_tools *tools, int status);
void	exec_err(t_tools *tools, int err, char *str, char *value);
void	wait_status(t_tools *tools, int pid, int *status);

/*src/executor/redirections.c*/
void	set_stdin(t_tools *tools, t_parser *parser, int fd);
t_lexer	*set_input(t_tools *tools, t_parser *parser, t_lexer *redirection,
			int fd);
void	set_stdout(t_parser *parser, int fd);
t_lexer	*set_output(t_parser *parser, t_lexer *redirection, int fd);
void	redirection(t_tools *tools, t_parser *parser, int *index);

/*src/executor/redirections_utils.c*/
void	set_stdin_flag(t_parser *parser, t_lexer *redirections);
void	set_stdout_flag(t_parser *parser, t_lexer *redirections);
int		get_digits_token(t_lexer *current);
int		set_fd(t_lexer *current, t_parser *parser);
void	std_err(int err, char *str);

/*src/executor/pipex.c*/
void	pipex_dup_and_close(int close_fd, int dup_fd, int dup_fd2);
void	minishell_pipex(t_tools *tools, t_parser *parser, int *index);

/*src/executor/here_doc.c*/
void	get_here_doc(t_tools *tools, int fd[2], char *delimiter);
void	here_doc(t_tools *tools, char *delimiter);
void	status_heredoc(t_tools *tools, int *status);
void	get_status(int *status);

/*src/executor/child_signals.c*/
void	eof_sig_msg(t_tools *tools, char *line, char *delimiter);
void	child_handler(int sig);
void	handle_child_sigaction(void);
void	here_doc_handler(int sig);
void	handle_heredoc_sigaction(void);

#endif