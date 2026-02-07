/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:30:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/07 22:14:38 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "repl.h"

#define INTERRUPTED -2

extern volatile sig_atomic_t	g_interrupt;

static int	create_heredoc_fd(char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == SYSCALL_ERROR)
		return (SYSCALL_ERROR);
	while (true)
	{
		g_interrupt = 0;
		line = readline("> ");
		if (g_interrupt)
			return (free(line), close(fd[0]), close(fd[1]), INTERRUPTED);
		if (!line || ft_strcmp(line, delimiter) == 0)
			return (free(line), close(fd[1]), fd[0]);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
}

static int	prepare_cmd_heredocs(t_redirect *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == AST_HEREDOC)
		{
			if (redir->heredoc_fd != HEREDOC_FD_UNSET)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = HEREDOC_FD_UNSET;
			}
			fd = create_heredoc_fd(redir->file);
			if (fd == INTERRUPTED)
				return (EXIT_SIGNAL_BASE + SIGINT);
			if (fd == SYSCALL_ERROR)
				return (EXIT_FAILURE);
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}

static int	prepare_heredoc_node(t_ast_node *node)
{
	int	status;

	if (!node)
		return (EXIT_SUCCESS);
	status = prepare_heredoc_node(node->left);
	if (status != EXIT_SUCCESS)
		return (status);
	if (node->type == NODE_CMD)
	{
		status = prepare_cmd_heredocs(node->data.cmd->redirects);
		if (status != EXIT_SUCCESS)
			return (status);
	}
	status = prepare_heredoc_node(node->right);
	if (status != EXIT_SUCCESS)
		return (status);
	return (EXIT_SUCCESS);
}

int	prepare_heredocs(t_ast_node *node)
{
	int	status;

	status = prepare_heredoc_node(node);
	if (status != EXIT_SUCCESS)
		close_prepared_heredocs(node);
	return (status);
}

void	close_prepared_heredocs(t_ast_node *node)
{
	t_redirect	*redir;

	if (!node)
		return ;
	close_prepared_heredocs(node->left);
	if (node->type == NODE_CMD)
	{
		redir = node->data.cmd->redirects;
		while (redir)
		{
			if (redir->type == AST_HEREDOC
				&& redir->heredoc_fd != HEREDOC_FD_UNSET)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = HEREDOC_FD_UNSET;
			}
			redir = redir->next;
		}
	}
	close_prepared_heredocs(node->right);
}
