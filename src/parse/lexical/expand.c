/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:33:14 by naoki             #+#    #+#             */
/*   Updated: 2026/02/08 13:33:14 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_internal.h"

static bool	append_dollar(t_strbuf *sb, char *raw, size_t *i, t_expand_ctx *ctx)
{
	size_t	name_len;

	if (raw[*i + 1] == '?')
	{
		if (!append_exit_status(sb, ctx->last_status))
			return (false);
		*i += 2;
		return (true);
	}
	name_len = env_name_len(raw, *i + 1);
	if (name_len == 0)
		return (sb_append_char(sb, raw[(*i)++]));
	if (!append_env_value(sb, raw, *i, ctx->env))
		return (false);
	*i += name_len + 1;
	return (true);
}

static bool	append_next(t_strbuf *sb, char *raw, size_t *i, t_expand_ctx *ctx)
{
	if (raw[*i] == '$')
		return (append_dollar(sb, raw, i, ctx));
	if (!sb_append_char(sb, raw[*i]))
		return (false);
	*i += 1;
	return (true);
}

static char	*expand_value(char *raw, t_expand_ctx *ctx)
{
	t_strbuf	sb;
	size_t		i;

	if (!sb_init(&sb))
		return (NULL);
	i = 0;
	while (raw[i])
	{
		if (!append_next(&sb, raw, &i, ctx))
			return (free(sb.buf), NULL);
	}
	return (sb.buf);
}

static void	expand_one_token(t_token *token, t_expand_ctx *ctx)
{
	char	*expanded;

	if (token->type != WORD || !token->has_env || token->single_quoted)
		return ;
	expanded = expand_value(token->value, ctx);
	if (!expanded)
		return ;
	free(token->value);
	token->value = expanded;
	token->has_env = false;
}

void	expand_tokens(t_token_list *list, t_env *env, int last_status)
{
	t_expand_ctx	ctx;
	size_t			i;

	if (!list)
		return ;
	ctx.env = env;
	ctx.last_status = last_status;
	i = 0;
	while (i < list->count)
	{
		expand_one_token(&list->tokens[i], &ctx);
		i++;
	}
}
