/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:14:22 by tshimizu          #+#    #+#             */
/*   Updated: 2025/12/21 18:14:39 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexical.h"
#include "minishell.h"


t_redir_type token_to_redir(t_token_type type)
{
    if (type == REDIR_IN) return AST_REDIR_IN;
    if (type == REDIR_OUT) return AST_REDIR_OUT;
    if (type == REDIR_APPEND) return AST_REDIR_APPEND;
    if (type == HEREDOC) return AST_HEREDOC;
    return AST_REDIR_INVALID;
}

bool	is_redirection(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

bool	is_redir_target(t_token *t, int i)
{
	if (i == 0)
		return (false);
	if (t[i].type != WORD)
		return (false);
	if (is_redirection(t[i-1].type))
		return (true);
	return (false);
}

bool has_redir_in_range(t_token *t, int l, int r)
{
    int i;

    i = l;
    while (i < r)
    {
        if (is_redirection(t[i].type))
            return (true);
        i++;
    }
    return (false);
}

t_ast_node	*new_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
    node->data.cmd = NULL;
	return (node);
}


t_ast_node	*new_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->data.cmd = NULL;
	return (node);
}

t_redirect	*new_redirect(t_redir_type type, char *value)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(value);
	redir->next = NULL;
	return (redir);
}


int	count_words_excluding_redirs(t_token *t, int l, int r)
{
	int	i;
	int	count;

	i = l;
	count = 0;
	while (i <= r)
	{
		if (t[i].type == WORD && !is_redir_target(t, i))
			count++;
		i++;
	}
	return (count);
}


char **extract_argv(t_token *t, int l, int r)
{
	int		i;
	int		count;
	char	**argv;

	count = count_words_excluding_redirs(t, l, r);
	argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);

    i = l;
	count = 0;
	while (i <= r)
	{
		if (t[i].type == WORD && !is_redir_target(t, i))
			argv[count++] = ft_strdup(t[i].value);
		i++;
	}
	argv[count] = NULL;
	return (argv);
}


t_redirect *extract_redirects(t_token *t, int l, int r)
{
	t_redirect	*head;
	t_redirect	*cur;
	int			i;

	head = NULL;
	cur = NULL;
	i = l;
	while (i <= r)
	{
		if (is_redirection(t[i].type))
		{
            if (i + 1 > r || t[i + 1].type != WORD)
                return (NULL);
			t_redirect *new = new_redirect(token_to_redir(t[i].type), t[i + 1].value);
			if (!head)
				head = new;
			else
				cur->next = new;
			cur = new;
			i += 2;
		}
		else
			i++;
	}
	return (head);
}

t_cmd_data *build_cmd_data(t_token *t, int l, int r)
{
	t_cmd_data	*cmd;

    cmd = malloc(sizeof(t_cmd_data));
    if (!cmd)
        return (NULL);

    cmd->argv = extract_argv(t, l, r);
    cmd->redirects = extract_redirects(t, l, r);
    if (!cmd->argv || (!cmd->redirects && has_redir_in_range(t, l, r)))
    {
        free(cmd);
        return (NULL);
    }

    return cmd;
}


t_ast_node *parse_cmd(t_token *t, int l, int r)
{
	t_ast_node	*node;
	t_cmd_data	*cmd;

	cmd = build_cmd_data(t, l, r);
	if (!cmd)
		return (NULL);
	node = new_ast_node(NODE_CMD);
	node->data.cmd = cmd;
	return (node);
}


t_ast_node *parse_pipeline(t_token *t, int l, int r)
{
	int	i;

	i = r;
	while (i >= l)
	{
		if (t[i].type == PIPE)
        {
            t_ast_node *left = parse_pipeline(t, l, i - 1);
            t_ast_node *right = parse_pipeline(t, i + 1, r);
            if (!left || !right)
                return (NULL);
            return (new_pipe_node(left, right));
        }
		i--;
	}
	return (parse_cmd(t, l, r));
}

t_ast_node *list_to_ast(t_token_list *token_list)
{
	return (parse_pipeline(token_list->tokens,0,token_list->count - 1));
}
