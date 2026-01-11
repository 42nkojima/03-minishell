/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:19:55 by tshimizu          #+#    #+#             */
/*   Updated: 2026/01/11 23:19:57 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_excluding_redirs(t_token *t, int l, int r)
{
	int	i;
	int	count;

	count = 0;
	i = l;
	while (i <= r)
	{
		if (t[i].type == WORD && !is_redir_target(t, i))
			count++;
		i++;
	}
	return (count);
}

char	**extract_argv(t_token *t, int l, int r)
{
	char	**argv;
	int		i;
	int		count;

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
		return (NULL);
	return (node);
}
