#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*executor.c*/
int		executor(t_tools *tools);
void	set_executor(t_parser *parser);
void	execute_cmd(t_tools *tools, t_parser *parser);

/*redirections.c*/
void	set_stdout(t_parser *parser);
void	set_stdin(t_parser *parser);
void	redirection(t_parser *parser);
char	*set_stdin_flag(t_parser *parser);
char	*set_stdout_flag(t_parser *parser);

/*here_doc.c*/
void	here_doc(char *limiter, int original_stdout);
void	get_here_doc(char *limiter, int fd, int original_stdout);

/*cmd_exec.c*/
void	exec_path(char **path_list, char **cmd_args, char **envp);
int		exec_builtins(t_parser *parser);
void	minishell_pipex(t_parser *parser, t_tools *tools);

#endif