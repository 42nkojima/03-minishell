/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:19:55 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/31 16:09:50 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_excluding_redirs(t_token *t, int l, int r)
{
	int	count;

	count = 0;
	while (l <= r)
	{
		if (t[l].type == WORD && !is_redir_target(t, l))
			count++;
		l++;
	}
	return (count);
}

char	**extract_argv(t_token *t, int l, int r)
{
	char	**argv;
	int		count;

	count = count_words_excluding_redirs(t, l, r);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	count = 0;
	while (l <= r)
	{
		if (t[l].type == WORD && !is_redir_target(t, l))
			argv[count++] = ft_strdup(t[l].value);
		l++;
	}
	argv[count] = NULL;
	return (argv);
}

t_cmd_data	*build_cmd_data(t_token *t, int l, int r)
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
	return (cmd);
}

t_ast_node	*parse_cmd(t_token *t, int l, int r)
{
	t_ast_node	*node;

	node = new_ast_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->data.cmd = build_cmd_data(t, l, r);
	if (!node->data.cmd)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
