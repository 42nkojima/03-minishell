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

static bool	sb_reserve(t_strbuf *sb, size_t extra)
{
	size_t	need;
	size_t	cap;
	char	*new_buf;

	need = sb->len + extra + 1;
	cap = sb->cap;
	while (cap < need)
		cap *= 2;
	if (cap == sb->cap)
		return (true);
	new_buf = malloc(cap);
	if (!new_buf)
		return (false);
	ft_memcpy(new_buf, sb->buf, sb->len + 1);
	free(sb->buf);
	sb->buf = new_buf;
	sb->cap = cap;
	return (true);
}

bool	sb_init(t_strbuf *sb)
{
	sb->cap = 16;
	sb->len = 0;
	sb->buf = malloc(sb->cap);
	if (!sb->buf)
		return (false);
	sb->buf[0] = '\0';
	return (true);
}

bool	sb_append_char(t_strbuf *sb, char c)
{
	if (!sb_reserve(sb, 1))
		return (false);
	sb->buf[sb->len] = c;
	sb->len++;
	sb->buf[sb->len] = '\0';
	return (true);
}

bool	sb_append_str(t_strbuf *sb, char *s)
{
	size_t	len;

	if (!s)
		return (true);
	len = ft_strlen(s);
	if (!sb_reserve(sb, len))
		return (false);
	ft_memcpy(sb->buf + sb->len, s, len);
	sb->len += len;
	sb->buf[sb->len] = '\0';
	return (true);
}
