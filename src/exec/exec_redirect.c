/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:25:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/07 13:25:00 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "repl.h"
#include <fcntl.h>

#define HEREDOC_INTERRUPTED -2

extern volatile sig_atomic_t	g_interrupt;

static int	print_redir_error(char *file)
{
	ft_putstr_fd("minishell: ", FD_STDERR);
	perror(file);
	return (EXIT_FAILURE);
}

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
			return (free(line), close(fd[0]), close(fd[1]), HEREDOC_INTERRUPTED);
		if (!line || ft_strcmp(line, delimiter) == 0)
			return (free(line), close(fd[1]), fd[0]);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
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
		return (create_heredoc_fd(redir->file));
	return (SYSCALL_ERROR);
}

static int	apply_one_redirect(t_redirect *redir)
{
	int	fd;

	fd = open_redir_fd(redir);
	if (fd == HEREDOC_INTERRUPTED)
		return (EXIT_SIGNAL_BASE + SIGINT);
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
