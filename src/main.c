/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:37:33 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/26 11:51:25 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
    int     fd;
    int     i;

    (void)argc;
    (void)argv;
    (void)envp;
    i = 1;
    fd = open(".minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
    while (1)
    {
        line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
        if (line == NULL)
        {
            printf("exit\n");
            break;
        }
        if (line && *line)
        {
            add_history(line);  
            ft_putnbr_fd(i++, fd);
            ft_putstr_fd(". ", fd);
            ft_putstr_fd(line, fd);
            ft_putstr_fd("\n", fd);
        }
        free(line);   
    }
    return (0);
}