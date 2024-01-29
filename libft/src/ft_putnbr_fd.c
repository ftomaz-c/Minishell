/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftomazc <ftomazc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:21:38 by ftomaz-c          #+#    #+#             */
/*   Updated: 2024/01/20 16:35:12 by ftomazc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Outputs the integer ’n’ to the given file descriptor.						*/
/*n: The integer to output.													*/
/*fd: The file descriptor on which to write.								*/

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2", fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		n = n % 10;
	}
	ft_putchar_fd(n + '0', fd);
}
