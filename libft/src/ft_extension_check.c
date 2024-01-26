/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:52:01 by ftomazc           #+#    #+#             */
/*   Updated: 2024/01/20 16:18:38 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	extension_check(char *file_name, char *extension)
{
	int	file_name_len;
	int extension_len;
   
	file_name_len = ft_strlen(file_name);
	extension_len = ft_strlen(extension);
	if (ft_strncmp(&file_name[file_name_len - extension_len], extension,\
	 extension_len) == 0)
		return (1) ;
	ft_putstr_fd("Error: Invalid File Format for file '", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
    ft_putstr_fd("'.\n", STDERR_FILENO);
	return (0);
}