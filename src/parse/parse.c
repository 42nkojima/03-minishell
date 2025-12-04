/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:11:40 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/29 16:40:03 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parse(char *input)
{
    char **result;

    result = tokenizer(input);
    if (!result)
        return(free(result),NULL);
    
    return result;
}
