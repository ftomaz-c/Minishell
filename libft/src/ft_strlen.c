/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:47:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/01/22 19:15:30 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Determines the length of string excluding the ending null character.		*/
/*Returns the length of string.												*/

#include "../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}
