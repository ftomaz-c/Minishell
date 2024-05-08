#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*src/executor/executor.c*/
void	exec_path(char **path_list, char **cmd_args, char **envp);
int		exec_builtins(t_tools *tools);
void	execute_cmd(t_tools *tools, t_parser *parser);
void	set_and_exec(t_tools *tools, t_parser *parser);
int		executor(t_tools *tools);

/*src/executor/executor_utils.c*/
void	free_and_exit(t_tools *tools);
void	exec_err(int err, char *str, char *value);
void	wait_status(int pid, int *status);

/*src/executor/redirections.c*/
void	set_stdin(t_tools *tools, t_parser *parser, int fd);
t_lexer	*set_input(t_tools *tools, t_parser *parser, t_lexer *redirection, int fd);
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
void	handle_pipex_sigaction(void);
void	get_here_doc(t_tools *tools, char *limiter, int fd[2], int original_stdout);
void	here_doc(t_tools *tools, char *limiter, int original_stdout);

#endif