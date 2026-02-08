/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/01 16:55:53 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "constants.h"
# include "minishell.h"
# include <sys/wait.h>
# include <unistd.h>

// executor.c
int		execute_command(t_command *cmd, t_env **env);

// command.c
char	*find_command(char *cmd, char **envp);

// execute_ast.c
int		execute_ast(t_ast_node *node, t_env **env);

// exec_redirect.c
int		apply_redirects(t_redirect *redir);

// exec_heredoc.c
int		prepare_heredocs(t_ast_node *node);
void	close_prepared_heredocs(t_ast_node *node);

// exec_stdio.c
int		save_stdio_fds(int saved[2]);
void	restore_stdio_fds(int saved[2]);

#endif
