/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:02:59 by ftomazc           #+#    #+#             */
/*   Updated: 2024/03/13 14:02:43 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	check_if_ll_range(const char *nptr, long long *result, int *i, int sign)
{
	long long	tmp;

	tmp = (*result) * sign;
	if (tmp > LLONG_MAX / 10
		|| (tmp == LLONG_MAX / 10 && nptr[*i] - '0' > LLONG_MAX % 10))
		errno = ERANGE;
	else if (tmp < LLONG_MIN / 10
		|| (tmp == LLONG_MIN / 10 && nptr[*i] - '0' > -(LLONG_MIN % 10)))
		errno = ERANGE;
	if (errno)
	{
		if (sign == -1)
			*result = LLONG_MIN;
		else
			*result = LLONG_MAX;
		return (0);
	}
	return (1);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	sign = 1;
	i = 0;
	result = 0;
	errno = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-' )
			sign *= -1;
		i++;
	}
	while (nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (!check_if_ll_range(nptr, &result, &i, sign))
			return (result);
		result = result * 10 + (nptr[i++] - '0');
	}
	return (result * sign);
}
