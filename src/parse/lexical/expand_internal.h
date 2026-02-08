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

typedef struct s_strbuf
{
	char	*buf;
	size_t	len;
	size_t	cap;
}				t_strbuf;

typedef struct s_expand_ctx
{
	t_env	*env;
	int		last_status;
}				t_expand_ctx;

bool	sb_init(t_strbuf *sb);
bool	sb_append_char(t_strbuf *sb, char c);
bool	sb_append_str(t_strbuf *sb, char *s);
size_t	env_name_len(char *s, size_t i);
bool	append_env_value(t_strbuf *sb, char *raw, size_t i, t_env *env);
bool	append_exit_status(t_strbuf *sb, int last_status);

#endif
