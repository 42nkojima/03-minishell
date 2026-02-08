/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:39:33 by naoki             #+#    #+#             */
/*   Updated: 2026/02/08 13:39:33 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	can_merge_joined_words(t_token *prev, t_token *current)
{
	return (prev->type == WORD && current->type == WORD && current->joins_prev);
}

static bool	merge_word_values(t_token *prev, t_token *current)
{
	char	*merged;

	merged = ft_strjoin(prev->value, current->value);
	if (!merged)
		return (false);
	free(prev->value);
	free(current->value);
	prev->value = merged;
	prev->has_env = false;
	prev->single_quoted = false;
	prev->is_quoted = prev->is_quoted || current->is_quoted;
	return (true);
}

static void	erase_token_preserving_joins(t_token_list *list, size_t index)
{
	bool	removed_joins_prev;

	removed_joins_prev = list->tokens[index].joins_prev;
	if (index + 1 < list->count && index == 0)
		list->tokens[index + 1].joins_prev = false;
	else if (index + 1 < list->count)
		list->tokens[index + 1].joins_prev = list->tokens[index + 1].joins_prev
			&& removed_joins_prev;
	free(list->tokens[index].value);
	while (index + 1 < list->count)
	{
		list->tokens[index] = list->tokens[index + 1];
		index++;
	}
	list->count--;
}

static void	merge_joined_words(t_token_list *list)
{
	size_t	read;
	size_t	write;

	read = 0;
	write = 0;
	while (read < list->count)
	{
		if (write > 0
			&& can_merge_joined_words(&list->tokens[write - 1],
				&list->tokens[read])
			&& merge_word_values(&list->tokens[write - 1], &list->tokens[read]))
		{
			read++;
			continue ;
		}
		if (write != read)
			list->tokens[write] = list->tokens[read];
		write++;
		read++;
	}
	list->count = write;
}

void	normalize_tokens(t_token_list *list)
{
	size_t	i;

	if (!list || list->count == 0)
		return ;
	i = 0;
	while (i < list->count)
	{
		if (list->tokens[i].type == WORD && !list->tokens[i].is_quoted
			&& list->tokens[i].value[0] == '\0')
		{
			erase_token_preserving_joins(list, i);
			continue ;
		}
		i++;
	}
	merge_joined_words(list);
}
