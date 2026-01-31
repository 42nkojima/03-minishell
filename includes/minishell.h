/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:48:22 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/24 11:40:01 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "ast.h"
# include "lexical.h"
# include "repl.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_command
{
	char		**argv;
	char		**envp;
}				t_command;

bool			init_signal_handlers(void);

void			free_token_list(t_token_list *list);
void			free_split(char **arr);
int				ft_isspace(int c);
void			free_ast(t_ast_node *node);
t_ast_node		*list_to_ast(t_token_list *token_list);
t_ast_node		*parse(char *input);
t_ast_node		*parse_pipeline(t_token *t, int l, int r);
t_ast_node		*new_ast_node(t_node_type type);
t_ast_node		*parse_cmd(t_token *t, int l, int r);
bool			is_redirection(t_token_type type);
t_redir_type	token_to_redir(t_token_type type);
bool			is_redir_target(t_token *t, int i);
t_redirect		*extract_redirects(t_token *t, int l, int r);
bool			has_redir_in_range(t_token *t, int l, int r);

#endif // MINISHELL_H
