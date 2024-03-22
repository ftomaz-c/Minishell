#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*src/utils/error.c*/
void	error_check(int argc, char **argv);

/*src/utils/history.c*/
void	write_in_history_file(char **line, int fd, char *file_path);
void	add_history_file(t_tools *tools, char *line, char *file_name);
void	append_to_history(char *line);
void	update_history(t_tools *tools, char *file_name);

/*src/utils/history_utils_1.c*/
int		check_empty_line(char *line);
size_t	ft_strlen_nl(const char *s);
int		history_section(char *line);
char	*get_file_path_from_home(t_tools *tools, char *file_name);

/*src/utils/history_utils_2.c*/
void	treat_line(char ***line_array, char *line);
void	add_line(char *line, char ***line_array, int fd, char *file_path);
int		check_line_count(int line_count, int fd);

/*src/utils/print.c*/
void	print_lexer(t_tools *tools);
void	print_parser_redirections(t_parser *parser);
void	print_parser(t_tools *tools);

/*src/utils/prompt.c*/
char	**handle_home_abreviation(t_tools *tools, char **str);
char	**generate_prompt(t_tools *tools);
char	*prompt_line(t_tools *tools);

/*src/utils/utils.c*/
int		find_next_char_position(char *str, int i, char c);
void	ft_lstaddback(t_lexer **lst, t_lexer *new);
int		count_chr(char *line, char c);
int		count_lines_in_file(const char *file_path);
void	free_list(char	**list);

#endif