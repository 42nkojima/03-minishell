/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:11:40 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 17:23:06 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse(char *input)
{
	t_token_list	*token_list;
	t_ast_node	*ast_root;

	token_list = tokenizer(input);
	if (!token_list || token_list -> error != ERR_NONE)
		return (NULL);
	ast_root = list_to_ast(token_list);
	return (ast_root);
}
