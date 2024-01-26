/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:54:53 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/01/20 16:36:12 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The  calloc()  function allocates memory for an array of nmemb elements	*/
/* of size bytes each and returns a pointer to the allocated memory.		*/
/* The memory is set to zero. If nmemb or size is 0, then calloc() returns	*/
/* either NULL, or a unique pointer value that can later be successfully	*/
/* passed to free(). If the multiplication of nmemb and size would result in*/
/* integer overflow, then calloc() returns an error.						*/
/*The  calloc() function return a pointer to the allocated memory, which is	*/
/* suitably aligned for any built-in type. On error, this function returns	*/
/* NULL. NULL may also be returned by a successful call to calloc() with	*/
/* nmemb or size equal to zero.												*/

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
	{
		ft_putstr_fd("Error: Failed to allocate memory (size: ", STDERR_FILENO);
		ft_putnbr_fd(nmemb * size, STDERR_FILENO);
		ft_putstr_fd(" bytes\n", STDERR_FILENO);
		return (NULL);
	}
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
