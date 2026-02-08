/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:32:03 by naoki             #+#    #+#             */
/*   Updated: 2026/02/08 13:32:03 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static bool	is_name_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static bool	is_name_char(char c)
{
	return (is_name_start(c) || ft_isdigit(c));
}

size_t	env_key_len(char *s, size_t i)
{
	size_t	len;

	if (!is_name_start(s[i]))
		return (0);
	len = 1;
	while (is_name_char(s[i + len]))
		len++;
	return (len);
}

bool	append_env_reference(t_expand_buf *buffer, char *raw, size_t i,
		t_env *env)
{
	size_t	len;
	char	*name;
	char	*env_value;

	len = env_key_len(raw, i + 1);
	name = ft_substr(raw, i + 1, len);
	if (!name)
		return (false);
	env_value = get_env_value(env, name);
	free(name);
	return (expand_buf_append_str(buffer, env_value));
}

bool	append_status_value(t_expand_buf *buffer, int last_status)
{
	char	*status_str;
	bool	ok;

	status_str = ft_itoa(last_status);
	if (!status_str)
		return (false);
	ok = expand_buf_append_str(buffer, status_str);
	free(status_str);
	return (ok);
}
