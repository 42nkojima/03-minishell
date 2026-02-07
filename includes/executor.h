/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/01/31 15:09:08 by nkojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "constants.h"
# include "minishell.h"
# include <sys/wait.h>
# include <unistd.h>

// executor.c
int		execute_command(t_command *cmd);

// command.c
char	*find_command(char *cmd, char **envp);

// execute_ast.c
int		execute_ast(t_ast_node *node);

// exec_redirect.c
int		apply_redirects(t_redirect *redir);

// exec_stdio.c
int		save_stdio_fds(int saved[2]);
void	restore_stdio_fds(int saved[2]);

#endif
