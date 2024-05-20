#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*src/executor/executor.c*/
void	exec_path(char **path_list, char **cmd_args, char **envp, int gnl);
int		exec_builtins(t_tools *tools);
void	execute_cmd(t_tools *tools, t_parser *parser);
void	set_and_exec(t_tools *tools, t_parser *parser);
int		executor(t_tools *tools);

/*src/executor/executor_utils.c*/
char	**basic_env(void);
void	free_and_exit(t_tools *tools);
void	exec_err(int err, char *str, char *value);
void	wait_status(t_tools *tools, int pid, int *status);

/*src/executor/redirections.c*/
void	set_stdin(t_tools *tools, t_parser *parser, int fd);
t_lexer	*set_input(t_tools *tools, t_parser *parser, t_lexer *redirection,
			int fd);
void	set_stdout(t_parser *parser, int fd);
t_lexer	*set_output(t_parser *parser, t_lexer *redirection, int fd);
void	redirection(t_tools *tools, t_parser *parser);

/*src/executor/redirections_utils.c*/
void	set_stdin_flag(t_parser *parser, t_lexer *redirections);
void	set_stdout_flag(t_parser *parser, t_lexer *redirections);
int		get_digits_token(t_lexer *current);
int		set_fd(t_lexer *current, t_parser *parser);
void	std_err(int err, char *str);

/*src/executor/pipex.c*/
void	pipex_dup_and_close(int close_fd, int dup_fd, int fd2);
void	minishell_pipex(t_tools *tools, t_parser *parser);

/*src/executor/here_doc.c*/
void	get_here_doc(t_tools *tools);
void	here_doc(t_tools *tools);

/*src/executor/child_signals.c*/
void	here_doc_sig(int sig);
void	sig_pipex_handler(int sig);
void	handle_pipex_sigaction(void (*handler)(int));
t_here_doc	*here_doc_struct(void);

void	handle_pipex_heredoc(void (*handler)(int));
void	eof_sig_msg_exit(t_tools *tools, char *line);
void	close_sig_exit(t_tools *tools, int fd, int status);

#endif