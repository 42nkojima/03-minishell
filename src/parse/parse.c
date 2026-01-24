/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:11:40 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/11 23:02:57 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse(char *input)
{
	t_token_list	*token_list;
	t_ast_node		*ast_root;

	token_list = tokenizer(input);
	if (!token_list)
		return (NULL);
	if (token_list->error != ERR_NONE)
	{
		free_token_list(token_list);
		return (NULL);
	}
	ast_root = list_to_ast(token_list);
	free_token_list(token_list);
	if (!ast_root)
		return (NULL);
	return (ast_root);
}
