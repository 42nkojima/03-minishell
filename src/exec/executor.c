/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2026/02/01 16:59:01 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../libs/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("minishell: ", FD_STDERR);
	ft_putstr_fd(cmd_name, FD_STDERR);
	ft_putendl_fd(": command not found", FD_STDERR);
	return (EXIT_CMD_NOT_FOUND);
}

static void	exec_child(char *cmd_path, t_command *cmd)
{
	execve(cmd_path, cmd->argv, cmd->envp);
	perror("minishell");
	free(cmd_path);
	exit(EXIT_CMD_NOT_EXECUTABLE);
}

static int	wait_and_get_status(pid_t pid, char *cmd_path)
{
	int	status;

	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	execute_builtin_command(t_command *cmd, t_env **env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(cmd->argv, *env));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (-1);
}

/*
** Execute external command with fork and execve
** @param cmd: Command structure with argv and envp
** @return: Exit status of the command
*/
int	execute_command(t_command *cmd, t_env **env)
{
	pid_t	pid;
	char	*cmd_path;
	int		status;

	status = execute_builtin_command(cmd, env);
	if (status != -1)
		return (status);
	cmd_path = find_command(cmd->argv[0], cmd->envp);
	if (!cmd_path)
		return (cmd_not_found(cmd->argv[0]));
	pid = fork();
	if (pid == SYSCALL_ERROR)
	{
		free(cmd_path);
		return (EXIT_FAILURE);
	}
	if (pid == SYSCALL_SUCCESS)
		exec_child(cmd_path, cmd);
	return (wait_and_get_status(pid, cmd_path));
}
