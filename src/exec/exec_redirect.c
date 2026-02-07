/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:25:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/07 22:21:43 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <fcntl.h>

static int	print_redir_error(char *file)
{
	ft_putstr_fd("minishell: ", FD_STDERR);
	perror(file);
	return (EXIT_FAILURE);
}

static int	open_redir_fd(t_redirect *redir)
{
	if (redir->type == AST_REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == AST_REDIR_OUT)
		return (open(redir->file, O_CREAT | O_WRONLY | O_TRUNC,
				FILE_PERMISSION));
	if (redir->type == AST_REDIR_APPEND)
		return (open(redir->file, O_CREAT | O_WRONLY | O_APPEND,
				FILE_PERMISSION));
	if (redir->type == AST_HEREDOC)
		return (redir->heredoc_fd);
	return (SYSCALL_ERROR);
}

static int	apply_one_redirect(t_redirect *redir)
{
	int	fd;

	fd = open_redir_fd(redir);
	if (fd == SYSCALL_ERROR)
	{
		if (redir->type != AST_HEREDOC)
			return (print_redir_error(redir->file));
		return (EXIT_FAILURE);
	}
	if (redir->type == AST_REDIR_OUT || redir->type == AST_REDIR_APPEND)
	{
		if (dup2(fd, FD_STDOUT) == SYSCALL_ERROR)
			return (close(fd), EXIT_FAILURE);
	}
	else if (dup2(fd, FD_STDIN) == SYSCALL_ERROR)
		return (close(fd), EXIT_FAILURE);
	close(fd);
	if (redir->type == AST_HEREDOC)
		redir->heredoc_fd = HEREDOC_FD_UNSET;
	return (EXIT_SUCCESS);
}

int	apply_redirects(t_redirect *redir)
{
	int	status;

	while (redir)
	{
		status = apply_one_redirect(redir);
		if (status != EXIT_SUCCESS)
			return (status);
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
