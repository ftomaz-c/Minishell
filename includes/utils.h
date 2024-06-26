/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:26:27 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/05/28 19:06:02 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*src/utils/error.c*/
void		error_check(int argc, char **argv);

/*src/utils/history.c*/
void		write_in_history_file(char **line, int fd, char *file_path);
void		add_history_file(t_tools *tools, char *line, char *file_name);
void		append_to_history(char *line);
void		update_history(t_tools *tools, char *file_name);

/*src/utils/history_utils.c*/
int			history_section(char *line);
void		treat_line(char ***line_array, char *line);
void		add_line(char *line, char ***line_array, int fd, char *file_path);
int			check_line_count(int line_count, int fd);

/*src/utils/print.c*/
void		print_lexer(t_tools *tools);
void		print_parser_redirections(t_parser *parser);
void		print_parser(t_tools *tools);

/*src/utils/prompt.c*/
char		**handle_home_abreviation(t_tools *tools, char **str);
char		**generate_prompt(t_tools *tools);
void		prompt_line(t_tools *tools);

/*src/utils/utils1.c*/
int			find_char_position(char *str, char c);
int			find_next_char_position(char *str, int i, char c);
int			count_chr(char *line, char c);
int			count_lines_in_file(const char *file_path);
int			count_lines(char **list);

/*src/utils/utils2.c*/
size_t		ft_strlen_nl(const char *s);
char		*get_file_path_from_home(char *home, char *file_name);
char		*get_var_from_env(char **env, char *var);
char		**get_env(char **envp);
void		free_list(char	**list);

/*src/utils/utils3.c*/
t_status	*global_status(void);
void		sort_array(char **env_copy);
int			check_empty_line(char *line);
int			ft_isspace_special(int c, int flag);
void		ft_lstaddback_lexer(t_lexer **lst, t_lexer *new);

#endif