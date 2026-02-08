/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:39:33 by naoki             #+#    #+#             */
/*   Updated: 2026/02/08 13:39:33 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	should_merge(t_token *prev, t_token *current)
{
	return (prev->type == WORD && current->type == WORD && current->glued_left);
}

static bool	merge_pair(t_token *prev, t_token *current)
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
	prev->quoted = prev->quoted || current->quoted;
	return (true);
}

static void	remove_token_at(t_token_list *list, size_t index)
{
	bool	removed_glued_left;

	removed_glued_left = list->tokens[index].glued_left;
	if (index + 1 < list->count && index == 0)
		list->tokens[index + 1].glued_left = false;
	else if (index + 1 < list->count)
		list->tokens[index + 1].glued_left = list->tokens[index
			+ 1].glued_left && removed_glued_left;
	free(list->tokens[index].value);
	while (index + 1 < list->count)
	{
		list->tokens[index] = list->tokens[index + 1];
		index++;
	}
	list->count--;
}

static void	merge_words(t_token_list *list)
{
	size_t	read;
	size_t	write;

	read = 0;
	write = 0;
	while (read < list->count)
	{
		if (write > 0
			&& should_merge(&list->tokens[write - 1], &list->tokens[read])
			&& merge_pair(&list->tokens[write - 1], &list->tokens[read]))
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

void	finalize_tokens(t_token_list *list)
{
	size_t	i;

	if (!list || list->count == 0)
		return ;
	i = 0;
	while (i < list->count)
	{
		if (list->tokens[i].type == WORD && !list->tokens[i].quoted
			&& list->tokens[i].value[0] == '\0')
		{
			remove_token_at(list, i);
			continue ;
		}
		i++;
	}
	merge_words(list);
}
