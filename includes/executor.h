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
void	exec_err(int err, char *str, char *value);
void	wait_status(int pid, int *status);

/*src/executor/redirections.c*/
void	redirection(t_parser *parser);
t_lexer	*set_output(t_parser *parser, t_lexer *redirection, int fd);
void	set_stdout(t_parser *parser, int fd);
t_lexer	*set_input(t_parser *parser, t_lexer *redirection, int fd);
void	set_stdin(t_parser *parser, int fd);

/*src/executor/redirections_utils.c*/
void	std_err(int err, char *str);
int		set_fd(t_lexer *current, t_parser *parser);
int		get_digits_token(t_lexer *current);
void	set_stdout_flag(t_parser *parser, t_lexer *redirections);
void	set_stdin_flag(t_parser *parser, t_lexer *redirections);

/*src/executor/pipex.c*/
void	minishell_pipex(t_tools *tools, t_parser *parser);

/*src/executor/here_doc.c*/
void	get_here_doc(char *limiter, int fd, int original_stdout);
void	here_doc(char *limiter, int original_stdout);

#endif