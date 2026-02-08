/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:28:35 by naoki             #+#    #+#             */
/*   Updated: 2026/02/08 13:28:35 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static bool	expand_buf_reserve(t_expand_buf *buffer, size_t extra)
{
	size_t	need;
	size_t	cap;
	char	*new_buf;

	need = buffer->len + extra + 1;
	cap = buffer->cap;
	while (cap < need)
		cap *= 2;
	if (cap == buffer->cap)
		return (true);
	new_buf = malloc(cap);
	if (!new_buf)
		return (false);
	ft_memcpy(new_buf, buffer->buf, buffer->len + 1);
	free(buffer->buf);
	buffer->buf = new_buf;
	buffer->cap = cap;
	return (true);
}

bool	expand_buf_init(t_expand_buf *buffer)
{
	buffer->cap = 16;
	buffer->len = 0;
	buffer->buf = malloc(buffer->cap);
	if (!buffer->buf)
		return (false);
	buffer->buf[0] = '\0';
	return (true);
}

bool	expand_buf_append_char(t_expand_buf *buffer, char c)
{
	if (!expand_buf_reserve(buffer, 1))
		return (false);
	buffer->buf[buffer->len] = c;
	buffer->len++;
	buffer->buf[buffer->len] = '\0';
	return (true);
}

bool	expand_buf_append_str(t_expand_buf *buffer, char *s)
{
	size_t	len;

	if (!s)
		return (true);
	len = ft_strlen(s);
	if (!expand_buf_reserve(buffer, len))
		return (false);
	ft_memcpy(buffer->buf + buffer->len, s, len);
	buffer->len += len;
	buffer->buf[buffer->len] = '\0';
	return (true);
}
