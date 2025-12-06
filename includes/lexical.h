/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:41 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/06 11:27:51 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_H
# define LEXICAL_H

#include <stdio.h>

typedef enum s_tokentype {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
} t_tokentype;

typedef struct s_token {
    t_tokentype type;
    char      *value;
} t_token;

typedef struct s_tokenlist {
    t_token  *tokens;
    size_t count;
} t_token_list;

t_token_list	*tokenizer(char *input);

#endif // LEXICAL_H
