#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*src/executor/executor.c*/
void	wait_status(int pid, int *status);
int		executor(t_tools *tools);
void	set_and_exec(t_tools *tools, t_parser *parser);
void	execute_cmd(t_tools *tools, t_parser *parser);

/*src/executor/redirections.c*/
void	set_stdin_flag(t_parser *parser, t_lexer *redirections);
void	set_stdout_flag(t_parser *parser, t_lexer *redirections);
void	set_stdout(t_parser *parser, int fd);
void	set_stdin(t_parser *parser, int fd);
void	redirection(t_parser *parser);

/*src/executor/here_doc.c*/
void	here_doc(char *limiter, int original_stdout);
void	get_here_doc(char *limiter, int fd, int original_stdout);

/*cmd_exec.c*/
void	exec_path(char **path_list, char **cmd_args, char **envp);
int		exec_builtins(t_tools *tools);
void	minishell_pipex(t_tools *tools, t_parser *parser);

void	std_err(int	err, char *str);

#endif