/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:42:34 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/15 13:54:46 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

static int	pipe_fork_fail(int fd[2], pid_t left)
{
	close(fd[0]);
	close(fd[1]);
	if (left > 0)
		waitpid(left, NULL, 0);
	return (EXIT_FAILURE);
}

static pid_t	fork_pipe_child(t_ast_node *pipe_node, int fd[2],
		int is_left, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid != SYSCALL_SUCCESS)
		return (pid);
	if (is_left)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (is_left)
		status = execute_ast(pipe_node->left, env);
	else
		status = execute_ast(pipe_node->right, env);
	free_ast(pipe_node);
	free_env_list(*env);
	exit(status);
}

static int	execute_cmd_node(t_ast_node *node, t_env **env)
{
	t_command	cmd;
	int			saved[2];
	int			status;

	if (save_stdio_fds(saved) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	status = apply_redirects(node->data.cmd->redirects);
	if (status == EXIT_SUCCESS)
	{
		if (!node->data.cmd->argv[0])
			status = EXIT_SUCCESS;
		else
		{
			cmd.argv = node->data.cmd->argv;
			cmd.envp = env_to_array(*env);
			if (!cmd.envp)
				return (ft_putendl_fd("minishell: failed to build envp", 2),
					restore_stdio_fds(saved), EXIT_FAILURE);
			status = execute_command(&cmd, env);
			free_envp(cmd.envp);
		}
	}
	restore_stdio_fds(saved);
	return (status);
}

static int	execute_pipe_node(t_ast_node *node, t_env **env)
{
	int		fd[2];
	pid_t	left;
	pid_t	right;
	int		status_right;

	if (pipe(fd) == SYSCALL_ERROR)
		return (EXIT_FAILURE);
	left = fork_pipe_child(node, fd, 1, env);
	if (left == SYSCALL_ERROR)
		return (pipe_fork_fail(fd, -1));
	right = fork_pipe_child(node, fd, 0, env);
	if (right == SYSCALL_ERROR)
		return (pipe_fork_fail(fd, left));
	close(fd[0]);
	close(fd[1]);
	waitpid(right, &status_right, 0);
	waitpid(left, NULL, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	return (EXIT_FAILURE);
}

int	execute_ast(t_ast_node *node, t_env **env)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd_node(node, env));
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(node, env));
	return (1);
}
