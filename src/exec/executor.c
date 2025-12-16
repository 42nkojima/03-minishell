/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkojima <nkojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by nkojima           #+#    #+#             */
/*   Updated: 2025/12/16 22:47:01 by nkojima          ###   ########.fr       */
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

/*
** Execute external command with fork and execve
** @param cmd: Command structure with argv and envp
** @return: Exit status of the command
*/
int	execute_command(t_command *cmd)
{
	pid_t	pid;
	char	*cmd_path;

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
