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

bool	add_token(t_token_list *list, t_token_init init)
{
	list->tokens[list->count].type = init.type;
	list->tokens[list->count].value = init.value;
	list->tokens[list->count].has_env = init.has_env;
	list->tokens[list->count].single_quoted = init.single_quoted;
	list->tokens[list->count].quoted = init.quoted;
	list->tokens[list->count].glued_left = init.glued_left;
	list->count++;
	return (true);
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

static size_t	tokenize_one(t_token_list *list, char *input, size_t i,
		bool glued_left)
{
	if (is_quote(input[i]))
		return (handle_quoted_word(list, input, i, glued_left));
	if (is_operator(input[i]))
		return (handle_operator(list, input, i));
	return (handle_word(list, input, i, glued_left));
}

static void	postprocess_tokens(t_token_list *list, t_env *env, int last_status)
{
	if (list->error != ERR_NONE)
		return ;
	expand_tokens(list, env, last_status);
	finalize_tokens(list);
}

t_token_list	*tokenizer(char *input, t_env *env, int last_status)
{
	t_token_list	*list;
	size_t			i;
	size_t			before_skip;
	bool			glued_left;
	if (!input)
		return (NULL);
	list = token_list_init(ft_strlen(input) + 1);
	if (!list)
		return (NULL);
	i = 0;
	while (input[i] && list->error == ERR_NONE)
	{
		before_skip = i;
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		glued_left = (list->count > 0 && before_skip == i);
		i = tokenize_one(list, input, i, glued_left);
	}
	postprocess_tokens(list, env, last_status);
	return (list);
}
