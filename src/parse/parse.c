/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:11:40 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 11:35:17 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parse(char *input)
{
    t_token_list *token_list;

    token_list = tokenizer(input);

    if (!token_list)
        return NULL;

}
