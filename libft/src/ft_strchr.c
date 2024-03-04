/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc < ftomaz-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:16:14 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/03/01 23:53:05 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The strchr() function returns a pointer to the first occurrence of the	*/
/*character c in the string s.	The function returns a pointer to the		*/
/*matched character or NULL if the character is not efound. The terminating	*/
/*null byte is considered part of the string, so that if c is specifid as	*/
/*'\0', these functions return a pointer to the terminator.					*/

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
