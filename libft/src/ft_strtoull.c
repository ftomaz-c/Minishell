/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:16:16 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/13 19:28:48 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	determine_base(const char *nptr, int *base, int *i)
{
	if (*base == 0)
	{
		if (nptr[*i] == '0')
		{
			if (nptr[*i + 1] == 'x' || nptr[*i + 1] == 'X')
			{
				*base = 16;
				(*i) += 2;
			}
			else if (nptr[*i + 1] == 'b' || nptr[*i + 1] == 'B')
			{
				*base = 2;
				(*i) += 2;
			}
			else
			{
				*base = 8;
				(*i)++;
			}
		}
		else
			*base = 10;
	}
}

unsigned long long int	convert_to_ull(const char *nptr, int base,
										int *i, unsigned long long result)
{
	while ((nptr[*i] >= '0' && nptr[*i] <= '9') || (base == 16 && ((nptr[*i] \
	>= 'a' && nptr[*i] <= 'f') || (nptr[*i] >= 'A' && nptr[*i] <= 'F'))))
	{
		if (nptr[*i] >= '0' && nptr[*i] <= '9')
		{
			if (result > ULLONG_MAX / base || (result == ULLONG_MAX / base
					&& (unsigned long long)(nptr[*i] - '0')
				> ULLONG_MAX % base))
				return (ULLONG_MAX);
			result = result * base + (nptr[*i] - '0');
		}
		else if (base == 16)
		{
			if (result > ULLONG_MAX / base || (result == ULLONG_MAX / base
					&& (unsigned long long)((nptr[*i] & ~0x20) - 'A' + 10)
				> ULLONG_MAX \
			% base))
				return (ULLONG_MAX);
			result = result * base + ((nptr[*i] & ~0x20) - 'A' + 10);
		}
		(*i)++;
	}
	return (result);
}

long long int	ft_strtoull(const char *nptr, char **endptr, int base)
{
	int					i;
	int					sign;
	long long			result;
	unsigned long long	nresult;

	sign = 1;
	i = 0;
	result = 0;
	nresult = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-' )
			sign *= -1;
		i++;
	}
	determine_base(nptr, &base, &i);
	result = convert_to_ull(nptr, base, &i, nresult);
	if (endptr != NULL)
		*endptr = (char *)&nptr[i];
	return (result * sign);
}
