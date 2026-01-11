/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:14:34 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 17:49:59 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast_node t_ast_node;

typedef enum e_redir_type
{
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_REDIR_APPEND,
	AST_HEREDOC,
    AST_REDIR_INVALID,
}						t_redir_type;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
}						t_node_type;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd_data
{
	char				**argv;
	t_redirect			*redirects;
}						t_cmd_data;


typedef union u_node_data
{
	t_cmd_data			*cmd;
	t_ast_node			*subshell;
}						t_node_data;

typedef struct s_ast_node
{
	t_node_type			type;
	t_node_data	data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;



#endif // AST_H
