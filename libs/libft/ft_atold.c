/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atold.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:05:42 by nkojima           #+#    #+#             */
/*   Updated: 2025/10/17 11:53:54 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts a string to a long double.
 *
 * Params:
 * @str: The string to convert.
 *
 * Return:
 * - The converted long double value.
 * - Handles optional '+' or '-' sign.
 * - Supports decimal point notation.
 */
long double	ft_atold(const char *str)
{
	long double	result;
	long double	power;
	int			sign;

	result = 0.0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		power = 0.1;
		while (ft_isdigit(*str))
		{
			result += (*str++ - '0') * power;
			power *= 0.1;
		}
	}
	return (sign * result);
}
