/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:25:25 by naoki             #+#    #+#             */
/*   Updated: 2026/02/08 13:25:25 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_INTERNAL_H
# define EXPAND_INTERNAL_H

# include "minishell.h"

typedef struct s_expand_buf
{
	char	*buf;
	size_t	len;
	size_t	cap;
}				t_expand_buf;

typedef struct s_expand_ctx
{
	t_env	*env;
	int		last_status;
}				t_expand_ctx;

bool	expand_buf_init(t_expand_buf *buffer);
bool	expand_buf_append_char(t_expand_buf *buffer, char c);
bool	expand_buf_append_str(t_expand_buf *buffer, char *s);
size_t	env_key_len(char *s, size_t i);
bool	append_env_reference(t_expand_buf *buffer, char *raw, size_t i,
			t_env *env);
bool	append_status_value(t_expand_buf *buffer, int last_status);

#endif
