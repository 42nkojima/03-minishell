/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:14:34 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/14 11:45:24 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_ast_node
{
    t_node_type         type;       // ノードの種類
    union u_node_data   data;       // ノード固有のデータ
    struct s_ast_node   *left;      // 左の子ノード
    struct s_ast_node   *right;     // 右の子ノード
}   t_ast_node;

typedef enum e_node_type
{
    NODE_CMD,           // 単一コマンド: echo hello
    NODE_PIPE,          // パイプ: cmd1 | cmd2
    NODE_AND,           // AND演算子: cmd1 && cmd2 (ボーナス)
    NODE_OR,            // OR演算子: cmd1 || cmd2 (ボーナス)
    NODE_SUBSHELL,      // サブシェル: (command) (ボーナス)
}   t_node_type;

typedef union u_node_data
{
    t_cmd_data      *cmd;       // NODE_CMD用
    // PIPE, AND, OR, SUBSHELLはleft/rightで表現
}   u_node_data;

typedef struct s_cmd_data
{
    char            **argv;         // 引数配列 ["echo", "hello", NULL]
    t_redirect      *redirects;     // リダイレクトリスト
}   t_cmd_data;

typedef struct s_redirect
{
    t_redir_type        type;       // リダイレクトタイプ
    char                *file;      // ファイル名またはデリミタ
    struct s_redirect   *next;      // 次のリダイレクト
}   t_redirect;

typedef enum e_redir_type
{
    REDIR_IN,       // <  入力リダイレクト
    REDIR_OUT,      // >  出力リダイレクト
    REDIR_APPEND,   // >> 追記リダイレクト
    HEREDOC,        // << ヒアドキュメント
}   t_redir_type;

#endif // AST_H
