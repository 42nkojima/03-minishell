/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:04 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 14:23:40 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_list_push(t_token_list *list, t_token_init init)
{
	list->tokens[list->count].type = init.type;
	list->tokens[list->count].value = init.value;
	list->tokens[list->count].has_env = init.has_env;
	list->tokens[list->count].single_quoted = init.single_quoted;
	list->tokens[list->count].is_quoted = init.is_quoted;
	list->tokens[list->count].joins_prev = init.joins_prev;
	list->count++;
}

static t_token_list	*token_list_init(size_t count)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->tokens = malloc(sizeof(t_token) * count);
	if (!list->tokens)
		return (free(list), NULL);
	list->count = 0;
	list->error = ERR_NONE;
	return (list);
}

static size_t	scan_next_token(t_token_list *list, char *s, size_t i,
		bool joins_prev)
{
	if (is_quote(s[i]))
		return (scan_quoted(list, s, i, joins_prev));
	if (is_operator(s[i]))
		return (scan_operator(list, s, i));
	return (scan_word(list, s, i, joins_prev));
}

static void	expand_and_normalize_tokens(t_token_list *list, t_env *env,
		int last_status)
{
	if (list->error != ERR_NONE)
		return ;
	expand_tokens(list, env, last_status);
	normalize_tokens(list);
}

t_token_list	*tokenizer(char *input, t_env *env, int last_status)
{
	t_token_list	*list;
	size_t			i;
	size_t			cursor_before_ws;
	bool			joins_prev;

	if (!input)
		return (NULL);
	list = token_list_init(ft_strlen(input) + 1);
	if (!list)
		return (NULL);
	i = 0;
	while (input[i] && list->error == ERR_NONE)
	{
		cursor_before_ws = i;
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		joins_prev = (list->count > 0 && cursor_before_ws == i);
		i = scan_next_token(list, input, i, joins_prev);
	}
	expand_and_normalize_tokens(list, env, last_status);
	return (list);
}
