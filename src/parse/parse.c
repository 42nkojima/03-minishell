/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:11:40 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 16:36:49 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse_result	*parse(char *input)
{
	t_token_list	*token_list;
	t_parse_result	*parse_result;

	token_list = tokenizer(input);
	if (!token_list)
		return (NULL);
	parse_result = malloc(sizeof(t_parse_result));
	parse_result->token_list = token_list;
	return (parse_result);
}
