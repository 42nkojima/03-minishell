/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:04 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/20 12:29:16 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_token(t_token_list *list, t_token_type type, char *value,
		bool has_env, bool single_quoted)
{
	list->tokens[list->count].type = type;
	list->tokens[list->count].value = value;
	list->tokens[list->count].has_env = has_env;
	list->tokens[list->count].single_quoted = single_quoted;
	list->count++;
	return (true);
}

t_token_list	*token_list_init(size_t count)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->tokens = malloc(sizeof(t_token) * count);
	if (!list->tokens)
		return (free(list), NULL);
	list->count = 0;
	return (list);
}

static size_t	skip_spaces(char *s, size_t i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

t_token_list	*tokenizer(char *input)
{
	t_token_list	*list;
	size_t			i;

	if (!input)
		return (NULL);
	list = token_list_init(ft_strlen(input) + 1);
	if (!list)
		return (NULL);
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_quote(input[i]))
			i = handle_quoted_word(list, input, i);
		else if (is_operator(input[i]))
			i = handle_operator(list, input, i);
		else
			i = handle_word(list, input, i);
	}
	return (list);
}
