/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:04 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/29 16:39:48 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical.h"
#include "minishell.h"


static void free_split(char **arr)
{
    size_t i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

static size_t count_split(char **arr)
{
    size_t i = 0;
    while (arr[i])
        i++;
    return i;
}

static t_tokentype validate_token_type(char *token)
{
    if (ft_strcmp(token, "|") == 0)
        return PIPE;
    if (ft_strcmp(token, "<") == 0)
        return REDIR_IN;
    if (ft_strcmp(token, ">") == 0)
        return REDIR_OUT;
    return WORD;
}

t_token_list *tokenizer(char *input)
{
    if (!input)
        return NULL;

    char **split = ft_split(input, ' ');
    if (!split)
        return NULL;

    t_token_list *list = malloc(sizeof(t_token_list));
    if (!list)
        return (free_split(split), NULL);

    size_t count = count_split(split);

    list->tokens = malloc(sizeof(t_token) * count);
    if (!list->tokens)
        return (free_split(split), free(list), NULL);

    list->count = count;

    size_t i = 0;
    while (i < count)
    {
        list->tokens[i].type = validate_token_type(split[i]);
        list->tokens[i].value = split[i];
        i++;
    }

    free(split);
    return list;
}
