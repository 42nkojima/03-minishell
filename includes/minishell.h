/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:22 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 17:47:38 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "lexical.h"
# include "repl.h"
#include "ast.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

bool				init_signal_handlers(void);

t_ast_node *parse_pipeline(t_token *t, int l, int r);

void				free_token_list(t_token_list *list);
void				free_split(char **arr);
int					ft_isspace(int c);
void	free_ast(t_ast_node *node);
t_ast_node *list_to_ast(t_token_list *token_list);
t_ast_node	*parse(char *input);

#endif // MINISHELL_H
