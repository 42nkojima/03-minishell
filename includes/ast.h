/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:14:34 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 14:02:16 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast_node
{
	t_node_type			type;
	union u_node_data	data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
}						t_node_type;

typedef union u_node_data
{
	t_cmd_data			*cmd;
}						t_node_data;

typedef struct s_cmd_data
{
	char				**argv;
	t_redirect			*redirects;
}						t_cmd_data;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}						t_redir_type;

#endif // AST_H
