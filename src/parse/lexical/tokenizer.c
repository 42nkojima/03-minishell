/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:04 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 11:28:22 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_split(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static t_token_type	validate_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	return (WORD);
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
	list->count = count;
	return (list);
}

bool	fill_tokens(t_token_list *list, char **split)
{
	size_t	i;

	i = 0;
	while (i < list->count)
	{
		list->tokens[i].type = validate_token_type(split[i]);
		list->tokens[i].value = split[i];
		i++;
	}
	return (true);
}

t_token_list	*tokenizer(char *input)
{
	char			**split;
	t_token_list	*list;
	size_t			count;

	if (!input)
		return (NULL);
	split = ft_split(input, ' ');
	if (!split)
		return (NULL);
	count = count_split(split);
	list = token_list_init(count);
	if (!list)
		return (free_split(split), NULL);
	if (!fill_tokens(list, split))
		return (free_token_list(list), free_split(split), NULL);
	free(split);
	return (list);
}
