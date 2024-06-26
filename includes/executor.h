/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomaz-c <ftomaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/27 18:21:29 by ftomaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*src/executor/executor.c*/
void	exec_path(t_tools *tools, char **cmd_args, char **envp);
int		simple_exec_and_buitlins(t_tools *tools, t_parser *parser);
void	execute_cmd(t_tools *tools, t_parser *parser, int index);
void	set_and_execute(t_tools *tools, t_parser *parser);
int		executor(t_tools *tools);

/*src/executor/executor_utils1.c*/
void	broadcast_signal(t_tools *tools, int num_pids, int signal);
void	free_and_exit(t_tools *tools, int status);
void	exec_err(t_tools *tools, int err, char *str);
void	wait_status(t_tools *tools, int pid, int *status);

/*src/executor/executor_utils2.c*/
void	child_waitpid(t_tools *tools, int *status);
void	execute_simple_cmd(t_tools *tools, t_parser *parser, char **env);
int		is_executable(t_tools *tools, char **cmd_args, char **envp);
int		is_valid(t_parser *parser);

/*src/executor/redirections.c*/
int		set_stdin(t_tools *tools, t_parser *parser, int fd);
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
void	status_heredoc(t_tools *tools, int *status, int pid);
void	get_status(int *status);

/*src/executor/child_signals.c*/
void	eof_sig_msg(t_tools *tools, char *line, char *delimiter);
void	child_handler(int sig);
void	handle_child_sigaction(void);
void	here_doc_handler(int sig);
void	handle_heredoc_sigaction(void);

#endif