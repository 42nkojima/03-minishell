/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:52:11 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/10 17:30:33 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	get_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

static bool	push_digit(
	unsigned long long *accumulator,
	unsigned long long limit,
	char c
)
{
	unsigned long long	digit;

	if (!ft_isdigit(c))
		return (false);
	digit = (unsigned long long)(c - '0');
	if (*accumulator > (limit - digit) / 10ULL)
		return (false);
	*accumulator = (*accumulator * 10ULL) + digit;
	return (true);
}

static void	set_value(long long *out, unsigned long long accumulator, int sign)
{
	if (sign > 0)
		*out = (long long)accumulator;
	else if (accumulator == (unsigned long long)LLONG_MAX + 1ULL)
		*out = LLONG_MIN;
	else
		*out = -(long long)accumulator;
}

bool	validate_str_to_ll(const char *s, long long *out)
{
	unsigned long long	accumulator;
	unsigned long long	max_abs_value;
	int					sign;

	if (!out || !s || !*s)
		return (false);
	sign = get_sign(&s);
	if (!ft_isdigit(*s))
		return (false);
	accumulator = 0;
	if (sign > 0)
		max_abs_value = (unsigned long long)LLONG_MAX;
	else
		max_abs_value = (unsigned long long)LLONG_MAX + 1ULL;
	while (*s)
	{
		if (!push_digit(&accumulator, max_abs_value, *s))
			return (false);
		s++;
	}
	set_value(out, accumulator, sign);
	return (true);
}
